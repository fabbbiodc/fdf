/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:36:19 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_cam_limits(t_mlx *fdf, t_pnt *min, t_pnt *max)
{
	int		i;
	int		j;
	t_pnt	p;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			p = fdf->map->points[i][j];
			p.x *= fdf->cam->theta;
			p.y *= fdf->cam->theta;
			p.z *= fdf->cam->z_move;
			ft_iso_proj(&p);
			ft_update_limits(&p, min, max);
			j++;
		}
		i++;
	}
}

void	ft_init_limits(t_bound *bounds)
{
	bounds->min_x = INFINITY;
	bounds->max_x = -INFINITY;
	bounds->min_y = INFINITY;
	bounds->max_y = -INFINITY;
}

void	ft_init_point(t_pnt *point, int value)
{
	point->x = value;
	point->y = value;
	point->z = value;
	point->color = value;
	point->depth = value;
}

void	ft_cam_fit(t_mlx *fdf)
{
	t_pnt	min;
	t_pnt	max;
	double	scale;

	if (fdf->cam->fitted)
		return ;
	scale = 40.0;
	while (scale > 0.1)
	{
		ft_init_point(&min, INT_MAX);
		ft_init_point(&max, INT_MIN);
		fdf->cam->theta = scale;
		fdf->cam->z_move = scale * 0.5;
		ft_cam_limits(fdf, &min, &max);
		if (max.x - min.x < WIN_WIDTH - 2 * MARGIN
			&& max.y - min.y < WIN_HEIGHT - 2 * MARGIN)
			break ;
		scale *= 0.95;
	}
	fdf->cam->fitted = 1;
	ft_center_map(fdf);
}

void	ft_cam_params(t_mlx *fdf)
{
	fdf->cam->proj = PROJ_ISO;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->theta = 1;
	fdf->cam->z_move = 0.1;
	fdf->cam->fitted = 0;
	fdf->cam->proj_distance = 1000.0;
	fdf->cam->spin_angle = 0;
	fdf->cam->color_scheme = 0;
	ft_cam_fit(fdf);
}
