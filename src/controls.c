/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:18 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:24:25 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_is_control_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT || key == KEY_PLU || key == KEY_MIN
		|| key == KEY_A || key == KEY_D || key == KEY_P
		|| key == KEY_O || key == KEY_L || key == KEY_W
		|| key == KEY_S || key == KEY_Q || key == KEY_E
		|| key == KEY_C);
}

void	ft_handle_move(int key, t_mlx *fdf)
{
	if (key == KEY_UP)
		fdf->cam->alpha += ROTATION;
	else if (key == KEY_DOWN)
		fdf->cam->alpha -= ROTATION;
	else if (key == KEY_LEFT)
		fdf->cam->beta -= ROTATION;
	else if (key == KEY_RIGHT)
		fdf->cam->beta += ROTATION;
	else if (key == KEY_Q)
		fdf->cam->spin_angle += ROTATION;
	else if (key == KEY_E)
		fdf->cam->spin_angle -= ROTATION;
	if (key == KEY_A)
		fdf->cam->x_move += MOVE;
	else if (key == KEY_D)
		fdf->cam->x_move -= MOVE;
	else if (key == KEY_S)
		fdf->cam->y_move -= MOVE;
	else if (key == KEY_W)
		fdf->cam->y_move += MOVE;
}

void	ft_handle_zoom(int key, t_mlx *fdf)
{
	if (key == KEY_PLU)
	{
		fdf->cam->theta += ZOOM;
		fdf->cam->z_move += ZOOM;
	}
	else if (key == KEY_MIN)
	{
		fdf->cam->theta -= ZOOM;
		fdf->cam->z_move -= ZOOM;
	}
}

void	ft_cam_control(int key, t_mlx *fdf)
{
	ft_handle_zoom(key, fdf);
	ft_handle_move(key, fdf);
	if (key == KEY_P)
		ft_toggle_projection(fdf);
	else if (key == KEY_O)
		fdf->cam->proj_distance += 50.0;
	else if (key == KEY_L)
		fdf->cam->proj_distance -= 50.0;
	else if (key == KEY_C)
		ft_toggle_color(fdf);
	fdf->cam->spin_angle = fmod(fdf->cam->spin_angle, 2 * M_PI);
}

void	ft_toggle_projection(t_mlx *fdf)
{
	if (fdf->cam->proj == PROJ_ISO)
	{
		fdf->cam->proj = PROJ_ORTHO;
		fdf->cam->alpha = 0;
		fdf->cam->beta = 0;
		fdf->cam->gamma = 0;
	}
	else if (fdf->cam->proj == PROJ_ORTHO)
		fdf->cam->proj = PROJ_1PT;
	else if (fdf->cam->proj == PROJ_1PT)
		fdf->cam->proj = PROJ_2PTS;
	else if (fdf->cam->proj == PROJ_2PTS)
		fdf->cam->proj = PROJ_ISO;
	ft_center_map(fdf);
}
