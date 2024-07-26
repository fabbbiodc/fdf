/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/26 16:05:10 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_cam_fit(t_mlx *fdf)
{
    t_point min, max;
    double scale;
    int i;
    int j;
    const double min_scale = 0.1;  // Minimum scale to prevent tiny maps

    if (fdf->cam->fitted)
        return ;

    scale = 40.0;  // Start with a larger scale

    while (scale > min_scale)
    {
        min = (t_point){INT_MAX, INT_MAX, INT_MAX, INT_MAX};
        max = (t_point){INT_MIN, INT_MIN, INT_MIN, INT_MIN};

        i = 0;
        while (i < fdf->map->height)
        {
            j = 0;
            while (j < fdf->map->width)
            {
                t_point p = fdf->map->points[i][j];
                p.x *= scale;
                p.y *= scale;
                p.z *= scale * 0.5;

                ft_iso_proj(&p);

                min.x = fmin(min.x, p.x);
                min.y = fmin(min.y, p.y);
                max.x = fmax(max.x, p.x);
                max.y = fmax(max.y, p.y);
                j++;
            }
            i++;
        }

        if (max.x - min.x < WIN_WIDTH - 2 * MARGIN && 
            max.y - min.y < WIN_HEIGHT - 2 * MARGIN)
            break;

        scale *= 0.95;  // Reduce scale more gradually
    }

    fdf->cam->theta = scale;
    fdf->cam->z_move = scale * 0.5;
    fdf->cam->x_move = (max.x + min.x) / 2;
    fdf->cam->y_move = (max.y + min.y) / 2;

    fdf->cam->fitted = 1;
}
int ft_cam_init(t_mlx *fdf)
{
    fdf->cam = (t_cam *)malloc(sizeof(t_cam));
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
    fdf->cam->fitted = 0;  // Initialize the fitted flag
}

void ft_cam_rotate(int key, t_mlx *fdf)
{
    if (key == KEY_UP)
        fdf->cam->alpha += ROTATION;
    else if (key == KEY_DOWN)
        fdf->cam->alpha -= ROTATION;
    else if (key == KEY_LEFT)
        fdf->cam->beta -= ROTATION;
    else if (key == KEY_RIGHT)
        fdf->cam->beta += ROTATION;
}
