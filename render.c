/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/09 16:08:59 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_iso_proj(t_point *p)
{
	double	x_iso;
	double	y_iso;
	x_iso = (p->x - p->y) * cos(RAD_30);
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z;
	p->x = x_iso;
	p->y = y_iso;
	p->x = x_iso + WIN_WIDTH / 2;
    p->y = y_iso + WIN_HEIGHT / 2;
}

int	ft_cam_init(t_mlx *fdf)
{
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
	 (ft_error_handle(ERR_CAM), ft_terminate(fdf));
	return (EXIT_SUCCESS);
}
void ft_cam_params(t_mlx *fdf)
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
}
void	ft_cam_rotate(int key, t_mlx *fdf)
{
	if (!fdf->cam)
		return ;
	if (key == KEY_UP)
		fdf->cam->alpha += 0.5;
	if (key == KEY_DOWN)
		fdf->cam->alpha -= 0.5;
}
int	ft_img_refresh(t_mlx *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	return(ft_init_image(fdf));
}

int	ft_render(t_point *p, t_mlx *mlx)
{
	double	z_start;



}