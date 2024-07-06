/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/06 18:12:57 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_iso_proj(t_point *p)
{
	const double scale = 0.82;
	double	x_iso;
	double	y_iso;
	x_iso = (p->x - p->y) * cos(RAD_30) * scale;
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z * scale;
	p->x = x_iso;
	p->y = y_iso;
}

int	ft_camera(t_mlx *mlx)
{
	
}