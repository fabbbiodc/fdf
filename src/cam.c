/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/27 00:13:16 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_cam_limits(t_mlx *fdf, t_point *min, t_point *max)
{
	int		i;
	int		j;
	t_point	p;

	i = -1;
	while (++i < fdf->map->height)
	{
		j = -1;
		while (++j < fdf->map->width)
		{
			p = fdf->map->points[i][j];
			p.x *= fdf->cam->theta;
			p.y *= fdf->cam->theta;
			p.z *= fdf->cam->z_move;
			ft_iso_proj(&p);
			min->x = fmin(min->x, p.x);
			min->y = fmin(min->y, p.y);
			max->x = fmax(max->x, p.x);
			max->y = fmax(max->y, p.y);
		}
	}
}

void	ft_cam_fit(t_mlx *fdf)
{
	t_point	min;
	t_point	max;
	double	scale;

	if (fdf->cam->fitted)
		return ;
	scale = 40.0;
	while (scale > 0.1)
	{
		min = (t_point){INT_MAX, INT_MAX, INT_MAX, INT_MAX};
		max = (t_point){INT_MIN, INT_MIN, INT_MIN, INT_MIN};
		fdf->cam->theta = scale;
		fdf->cam->z_move = scale * 0.5;
		ft_cam_limits(fdf, &min, &max);
		if (max.x - min.x < WIN_WIDTH - 2 * MARGIN
			&& max.y - min.y < WIN_HEIGHT - 2 * MARGIN)
			break ;
		scale *= 0.95;
	}
	fdf->cam->x_move = (max.x + min.x) / 2;
	fdf->cam->y_move = (max.y + min.y) / 2;
	fdf->cam->fitted = 1;
}

void	ft_cam_params(t_mlx *fdf)
{
	fdf->cam->projection = PROJ_ISO;
	fdf->cam->x_move = WIN_WIDTH / 2;
	fdf->cam->y_move = WIN_HEIGHT / 2;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->theta = 1;
	fdf->cam->z_move = 0.1;
	fdf->cam->fitted = 0;
	fdf->cam->proj_distance = 1000.0;
}

void	ft_cam_control(int key, t_mlx *fdf)
{
	if (key == KEY_UP)
		fdf->cam->alpha += ROTATION;
	else if (key == KEY_DOWN)
		fdf->cam->alpha -= ROTATION;
	else if (key == KEY_LEFT)
		fdf->cam->beta -= ROTATION;
	else if (key == KEY_RIGHT)
		fdf->cam->beta += ROTATION;
	else if (key == KEY_PLU)
	{
		fdf->cam->theta += ZOOM;
		fdf->cam->z_move += ZOOM;
	}
	else if (key == KEY_MIN)
	{
		fdf->cam->theta -= ZOOM;
		fdf->cam->z_move -= ZOOM;
	}
	else if (key == KEY_A)
		fdf->cam->x_move += MOVE;
	else if (key == KEY_D)
		fdf->cam->x_move -= MOVE;
	else if (key == KEY_S)
		fdf->cam->y_move -= MOVE;
	else if (key == KEY_W)
		fdf->cam->y_move += MOVE;
	else if (key == KEY_P)
		ft_toggle_projection(fdf);
	else if (key == KEY_O)
		fdf->cam->proj_distance += 50.0;
	else if (key == KEY_L)
		fdf->cam->proj_distance = fmax(50.0, fdf->cam->proj_distance - 50.0);
}

void	ft_toggle_projection(t_mlx *fdf)
{
	if (fdf->cam->projection == PROJ_ISO)
		fdf->cam->projection = PROJ_ORTHO;
	else if (fdf->cam->projection == PROJ_ORTHO)
		fdf->cam->projection = PROJ_1PT;
	else if (fdf->cam->projection == PROJ_1PT)
		fdf->cam->projection = PROJ_2PTS;
	else if (fdf->cam->projection == PROJ_2PTS)
		fdf->cam->projection = PROJ_ISO;
}
