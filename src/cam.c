/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/14 20:12:51 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_cam_init(t_mlx *fdf)
{
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
		(ft_error_handle(ERR_CAM), ft_terminate(fdf));
	return (EXIT_SUCCESS);
}

void	ft_cam_params(t_mlx *fdf)
{
	fdf->cam->projection = PROJ_ISO;
	if (fdf->cam->projection == PROJ_ISO)
	{
		fdf->cam->x_move = WIN_WIDTH / 2;
		fdf->cam->y_move = WIN_HEIGHT / 2;
	}
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->theta = 1;
}

void	ft_cam_rotate(int key, t_mlx *fdf)
{
	if (!fdf->cam)
		return ;
	if (key == KEY_UP)
		fdf->cam->alpha += ROTATION;
	if (key == KEY_DOWN)
		fdf->cam->alpha -= ROTATION;
}
