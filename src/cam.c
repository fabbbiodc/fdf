/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:11:03 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_cam_limits:
Calculates the minimum and maximum coordinates of the transformed map points.
// Called from:
ft_cam_fit
// Output:
Updates min and max point structures passed as parameters.*/
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

/* ft_init_limits:
Initializes the boundary structure with extreme values.
// Called from:
ft_center_map
// Output:
Modifies the bounds structure directly.*/
void	ft_init_limits(t_bound *bounds)
{
	bounds->min_x = INFINITY;
	bounds->max_x = -INFINITY;
	bounds->min_y = INFINITY;
	bounds->max_y = -INFINITY;
}

/* ft_init_point:
Initializes all components of a point structure with a given value.
// Called from:
ft_cam_fit
// Output:
Modifies the point structure directly.*/
void	ft_init_point(t_pnt *point, int value)
{
	point->x = value;
	point->y = value;
	point->z = value;
	point->color = value;
	point->depth = value;
}

/* ft_cam_fit:
Adjusts the camera parameters to fit the entire map within the window.
// Called from:
ft_fdf_init
// Output:
Updates camera parameters in the fdf structure.*/
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

/* ft_cam_params:
Initializes or resets all camera parameters to their default values.
// Called from:
ft_cam_init, ft_fdf_init
// Output:
Modifies camera parameters in the fdf structure.*/
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
