/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/28 00:41:08 by fdi-cecc         ###   ########.fr       */
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

void ft_one_point_proj(t_point *p, t_cam *cam)
{
    double x_persp, y_persp, z_persp;
    t_matrix iso_rot;
    t_point rotated;

    rotated = *p;
    iso_rot = ft_matr_rot_x(RAD_30);
    ft_rotate(iso_rot, &rotated);
    rotated.z = -rotated.z;

    z_persp = rotated.z + cam->proj_distance;
    if (z_persp <= 0) {
        p->x = p->y = INFINITY;
        return;
    }

    x_persp = (rotated.x * cam->proj_distance) / z_persp;
    y_persp = (rotated.y * cam->proj_distance) / z_persp;

    p->x = x_persp;
    p->y = y_persp;
    p->depth = z_persp;  // Store the depth
}

void ft_two_point_proj(t_point *p, t_cam *cam)
{
    double x_persp, y_persp, z_persp;
    t_point rotated;
    t_matrix iso_rot;

    rotated = *p;
    iso_rot = ft_matr_rot_x(RAD_30);
    ft_rotate(iso_rot, &rotated);
    rotated.z = -rotated.z;

    z_persp = rotated.z + cam->proj_distance;
    if (z_persp <= 0) {
        p->x = p->y = INFINITY;
        return;
    }

    x_persp = (rotated.x * cam->proj_distance) / z_persp;
    y_persp = (rotated.y * cam->proj_distance) / z_persp;

    p->x = x_persp - (rotated.y / 4);
    p->y = y_persp;
    p->depth = z_persp;  // Store the depth
}

void	ft_ortho_proj(t_point *p)
{
	t_matrix	iso_rot;

	iso_rot = ft_matr_rot_x(RAD_30);
	ft_rotate(iso_rot, p);
	p->z = -p->z;
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

void	ft_scale(t_point *p, t_cam *cam)
{
	p->x *= cam->theta;
	p->y *= cam->theta;
	p->z *= cam->z_move;
}

void	ft_center(t_point *p, t_cam *cam)
{
	double	iso_offset_y;
	double	depth_offset;

	p->x -= cam->x_move;
	p->y -= cam->y_move;
	iso_offset_y = (cam->map_width + cam->map_height) * sin(RAD_30) / 2;
	p->x += WIN_WIDTH / 2;
	p->y += (WIN_HEIGHT / 2) - (iso_offset_y * cam->theta);
	depth_offset = cam->map_depth * cam->z_move / 2;
	p->y -= depth_offset;
}

static void	ft_apply_transformations(t_point *p, t_mlx *fdf)
{
	t_matrix	final_rot;

	p->x *= fdf->cam->theta;
	p->y *= fdf->cam->theta;
	p->z *= fdf->cam->z_move;
	final_rot = ft_matr_final(fdf);
	ft_rotate(final_rot, p);
}

void ft_render(t_point *p, t_mlx *fdf)
{
    ft_apply_transformations(p, fdf);
    
    // Apply spin rotation
    double cos_spin = cos(fdf->cam->spin_angle);
    double sin_spin = sin(fdf->cam->spin_angle);
    double x = p->x;
    double y = p->y;
    p->x = x * cos_spin - y * sin_spin;
    p->y = x * sin_spin + y * cos_spin;

    p->depth = 0; // Initialize depth to 0 (no fading)

    if (fdf->cam->projection == PROJ_ISO)
        ft_iso_proj(p);
    else if (fdf->cam->projection == PROJ_1PT)
        ft_one_point_proj(p, fdf->cam);
    else if (fdf->cam->projection == PROJ_2PTS)
        ft_two_point_proj(p, fdf->cam);
    else if (fdf->cam->projection == PROJ_ORTHO)
        ft_ortho_proj(p);

    if (isinf(p->x) || isinf(p->y)) {
        p->x = p->y = INFINITY; // Point is not renderable
        return;
    }

    p->x -= fdf->cam->x_move;
    p->y -= fdf->cam->y_move;
    p->x += WIN_WIDTH / 2;
    p->y += WIN_HEIGHT / 2;

    // Clamp values to prevent extreme projections
    p->x = fmax(fmin(p->x, WIN_WIDTH * 2), -WIN_WIDTH);
    p->y = fmax(fmin(p->y, WIN_HEIGHT * 2), -WIN_HEIGHT);
}
