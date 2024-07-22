/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/22 15:20:01 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_iso_proj(t_point *p)
{
	double	x_iso;
	double	y_iso;

	x_iso = (p->x - p->y) * cos(RAD_30);
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z;
	p->x = x_iso + WIN_WIDTH / 2;
	p->y = y_iso + WIN_HEIGHT / 2;
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

void	ft_scale(t_point *p, double theta)
{
	p->x *= theta / 2;
	p->y *= theta / 2;
	p->z *= theta / 2;
}

void	ft_center(t_point *p, double x_move, double y_move)
{
	p->x = p->x + x_move - WIN_WIDTH / 4;
	p->y = p->y + y_move - WIN_HEIGHT / 4;
	if (p->x < 10)
		p->x = 10;
	if (p->x >= WIN_WIDTH - 10)
		p->x = WIN_WIDTH - 10;
	if (p->y < 10)
		p->y = 10;
	if (p->y >= WIN_HEIGHT - 10)
		p->y = WIN_HEIGHT - 10;
}

void	ft_render(t_point *p, t_mlx *fdf)
{
	t_matrix	rotation;

	ft_printf("Before render: (%f, %f, %f)\n", p->x, p->y, p->z);
	rotation = ft_matr_final(fdf);
	ft_rotate(rotation, p);
	ft_scale(p, fdf->cam->theta);
	if (fdf->cam->projection == PROJ_ISO)
		ft_iso_proj(p);
	ft_center(p, fdf->cam->x_move, fdf->cam->y_move);
	ft_printf("After render: (%f, %f, %f)\n", p->x, p->y, p->z);
}
