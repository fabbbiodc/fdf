/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:12:44 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:36:19 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_apply_projection(t_pnt *temp, t_mlx *fdf)
{
	if (fdf->cam->proj == PROJ_ISO)
		ft_iso_proj(temp);
	else if (fdf->cam->proj == PROJ_1PT)
		ft_one_point_proj(temp, fdf->cam);
	else if (fdf->cam->proj == PROJ_2PTS)
		ft_two_point_proj(temp, fdf->cam);
	else if (fdf->cam->proj == PROJ_ORTHO)
		ft_ortho_proj(temp);
}

void	ft_iso_proj(t_pnt *p)
{
	double	x_iso;
	double	y_iso;

	x_iso = (p->x - p->y) * cos(RAD_30);
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z;
	p->x = x_iso;
	p->y = y_iso;
}

void	ft_one_point_proj(t_pnt *p, t_cam *cam)
{
	double		x_persp;
	double		y_persp;
	double		z_persp;
	t_matrix	iso_rot;
	t_pnt		rotated;

	rotated = *p;
	iso_rot = ft_matr_rot_x(RAD_30);
	ft_rotate(iso_rot, &rotated);
	rotated.z = -rotated.z;
	z_persp = rotated.z + cam->proj_distance;
	if (z_persp <= 0)
	{
		p->x = INFINITY;
		p->y = INFINITY;
		return ;
	}
	x_persp = (rotated.x * cam->proj_distance) / z_persp;
	y_persp = (rotated.y * cam->proj_distance) / z_persp;
	p->x = x_persp;
	p->y = y_persp;
	p->depth = z_persp;
}

void	ft_two_point_proj(t_pnt *p, t_cam *cam)
{
	double		x_persp;
	double		y_persp;
	double		z_persp;
	t_pnt		rotated;
	t_matrix	iso_rot;

	rotated = *p;
	iso_rot = ft_matr_rot_x(RAD_30);
	ft_rotate(iso_rot, &rotated);
	rotated.z = -rotated.z;
	z_persp = rotated.z + cam->proj_distance;
	if (z_persp <= 0)
	{
		p->x = INFINITY;
		p->y = INFINITY;
		return ;
	}
	x_persp = (rotated.x * cam->proj_distance) / z_persp;
	y_persp = (rotated.y * cam->proj_distance) / z_persp;
	p->x = x_persp - (rotated.y / 4);
	p->y = y_persp;
	p->depth = z_persp;
}

void	ft_ortho_proj(t_pnt *p)
{
	t_matrix	iso_rot;

	iso_rot = ft_matr_rot_x(RAD_180);
	ft_rotate(iso_rot, p);
	p->z = -p->z;
}
