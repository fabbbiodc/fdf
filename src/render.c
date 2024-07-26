/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/26 23:16:56 by fdi-cecc         ###   ########.fr       */
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

void	ft_one_point_proj(t_point *p, t_cam *cam)
{
	double	x_rotated;
	double	y_rotated;
	double	z_rotated;
	double	x_perspective;
	double	y_perspective;

	// Apply initial rotation similar to isometric view
	x_rotated = p->x;
	y_rotated = p->y * cos(RAD_30) - p->z * sin(RAD_30);
	z_rotated = p->y * sin(RAD_30) + p->z * cos(RAD_30);

	// Apply perspective projection
	x_perspective = (x_rotated * cam->proj_distance) / (z_rotated + cam->proj_distance);
	y_perspective = (y_rotated * cam->proj_distance) / (z_rotated + cam->proj_distance);

	p->x = x_perspective;
	p->y = y_perspective;
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

void	ft_render(t_point *p, t_mlx *fdf)
{
	t_matrix	rot_x;
	t_matrix	rot_y;
	t_matrix	rot_z;
	t_matrix	final_rot;

	p->x *= fdf->cam->theta;
	p->y *= fdf->cam->theta;
	p->z *= fdf->cam->z_move;
	rot_x = ft_matr_rot_x(fdf->cam->alpha);
	rot_y = ft_matr_rot_y(fdf->cam->beta);
	rot_z = ft_matr_rot_z(fdf->cam->gamma);
	final_rot = ft_matr_mult(rot_y, rot_x);
	final_rot = ft_matr_mult(rot_z, final_rot);
	ft_rotate(final_rot, p);
	if (fdf->cam->projection == PROJ_ISO)
		ft_iso_proj(p);
	else if (fdf->cam->projection == PROJ_1PT)
		ft_one_point_proj(p, fdf->cam);
	p->x -= fdf->cam->x_move;
	p->y -= fdf->cam->y_move;
	p->x += WIN_WIDTH / 2;
	p->y += WIN_HEIGHT / 2;
	p->x = fmax(0, fmin(p->x, WIN_WIDTH - 1));
	p->y = fmax(0, fmin(p->y, WIN_HEIGHT - 1));
}
