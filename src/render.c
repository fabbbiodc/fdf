/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/26 14:46:31 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_iso_proj(t_point *p)
{
	double	x_iso;
	double	y_iso;

	x_iso = (p->x - p->y) * cos(RAD_30);
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z;
	p->x = x_iso;
	p->y = y_iso;
}

void	ft_rotate(t_matrix rot, t_point *p)
{
	double	x;
	double	y;
	double	z;

	x = rot.matrix[0][0] * p->x + rot.matrix[0][1]
		* p->y + rot.matrix[0][2] * p->z;
	y = rot.matrix[1][0] * p->x + rot.matrix[1][1]
		* p->y + rot.matrix[1][2] * p->z;
	z = rot.matrix[2][0] * p->x + rot.matrix[2][1]
		* p->y + rot.matrix[2][2] * p->z;
	p->x = x;
	p->y = y;
	p->z = z;
}

void ft_scale(t_point *p, t_cam *cam)
{
    p->x *= cam->theta;
    p->y *= cam->theta;
    p->z *= cam->z_move;
}

void ft_center(t_point *p, t_cam *cam)
{
    // Remove the map's center offset
    p->x -= cam->x_move;
    p->y -= cam->y_move;

    // Apply isometric offset
    double iso_offset_y = (cam->map_width + cam->map_height) * sin(RAD_30) / 2;

    // Center in the window
    p->x += WIN_WIDTH / 2;
    p->y += (WIN_HEIGHT / 2) - (iso_offset_y * cam->theta);

    // Add a dynamic vertical offset based on the map's depth
    double depth_offset = cam->map_depth * cam->z_move / 2;
    p->y -= depth_offset;
}

void ft_render(t_point *p, t_mlx *fdf)
{
    t_matrix rotation_x, rotation_y, rotation_z, final_rotation;

    // Scale
    p->x *= fdf->cam->theta;
    p->y *= fdf->cam->theta;
    p->z *= fdf->cam->z_move;

    // Create rotation matrices
    rotation_x = ft_matr_rot_x(fdf->cam->alpha);
    rotation_y = ft_matr_rot_y(fdf->cam->beta);
    rotation_z = ft_matr_rot_z(fdf->cam->gamma);

    // Combine rotations
    final_rotation = ft_matr_mult(rotation_y, rotation_x);
    final_rotation = ft_matr_mult(rotation_z, final_rotation);

    // Apply rotations
    ft_rotate(final_rotation, p);

    // Apply isometric projection
    ft_iso_proj(p);

    // Center the map
    p->x -= fdf->cam->x_move;
    p->y -= fdf->cam->y_move;

    // Move to screen center
    p->x += WIN_WIDTH / 2;
    p->y += WIN_HEIGHT / 2;

    // Ensure the point is within the window bounds
    p->x = fmax(0, fmin(p->x, WIN_WIDTH - 1));
    p->y = fmax(0, fmin(p->y, WIN_HEIGHT - 1));
}
