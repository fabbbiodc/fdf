/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/25 12:29:29 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_cam_fit(t_mlx *fdf)
{
    t_point min = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
    t_point max = {INT_MIN, INT_MIN, INT_MIN, INT_MIN};
    int i, j;

    // Find min and max values
    for (i = 0; i < fdf->map->height; i++) {
        for (j = 0; j < fdf->map->width; j++) {
            t_point p = fdf->map->points[i][j];
            ft_iso_proj(&p);  // Apply isometric projection
            min.x = fmin(min.x, p.x);
            min.y = fmin(min.y, p.y);
            min.z = fmin(min.z, p.z);
            max.x = fmax(max.x, p.x);
            max.y = fmax(max.y, p.y);
            max.z = fmax(max.z, p.z);
        }
    }

    // Calculate scale factors
    double scale_x = (WIN_WIDTH - 2 * MARGIN) / (max.x - min.x);
    double scale_y = (WIN_HEIGHT - 2 * MARGIN) / (max.y - min.y);

    fdf->cam->theta = fmin(scale_x, scale_y);
    fdf->cam->z_move = fdf->cam->theta / 5;  // Adjust this factor as needed

    // Calculate the center offset
    fdf->cam->x_move = (max.x + min.x) / 2;
    fdf->cam->y_move = (max.y + min.y) / 2;
}

int	ft_cam_init(t_mlx *fdf)
{
	fdf->cam = malloc(sizeof(t_cam));
	if (!fdf->cam)
	{
		ft_error_handle(ERR_CAM);
		ft_terminate(fdf);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void ft_cam_params(t_mlx *fdf)
{
    fdf->cam->projection = PROJ_ISO;
    fdf->cam->x_move = WIN_WIDTH / 2;
    fdf->cam->y_move = WIN_HEIGHT / 2;
    fdf->cam->alpha = 0;
    fdf->cam->beta = 0;
    fdf->cam->gamma = 0;
    fdf->cam->theta = 1;
    fdf->cam->z_move = 0.1;
    ft_cam_fit(fdf);
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
