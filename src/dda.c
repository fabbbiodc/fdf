/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:15:37 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 18:31:13 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_dda(t_mlx *fdf, t_pnt *p1, t_pnt *p2)
{
	t_pnt	delta;
	t_pnt	step;
	t_pnt	current;
	int		steps;

	if (isinf(p1->x) || isinf(p1->y) || isinf(p2->x) || isinf(p2->y))
		return ;
	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	steps = (int)fmax(fabs(delta.x), fabs(delta.y));
	if (steps == 0)
		return ;
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	current = *p1;
	ft_dda_loop(fdf, &current, p1, p2);
}

void	ft_dda_loop(t_mlx *fdf, t_pnt *current, t_pnt *p1, t_pnt *p2)
{
	double	progress;
	double	max_depth;
	int		x;
	int		y;
	int		color;

	progress = 0;
	max_depth = fdf->cam->proj_distance * 2;
	while (progress <= 1)
	{
		x = (int)round(current->x);
		y = (int)round(current->y);
		if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		{
			color = ft_color_gradient(p1->color, p2->color, progress);
			if (fdf->cam->proj == PROJ_1PT || fdf->cam->proj == PROJ_2PTS)
				color = ft_fade_color(color, p1->depth + (p2->depth - p1->depth)
						* progress, max_depth);
			ft_putpixel(fdf, x, y, color);
		}
		ft_update_current(current, p1, p2, &progress);
	}
}

void	ft_update_current(t_pnt *current, t_pnt *p1, t_pnt *p2,
		double *progress)
{
	t_pnt	delta;
	t_pnt	step;
	int		steps;

	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	steps = (int)fmax(fabs(delta.x), fabs(delta.y));
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	current->x += step.x;
	current->y += step.y;
	*progress += 1.0 / steps;
	if (fabs(current->x - p1->x) > fabs(delta.x)
		|| fabs(current->y - p1->y) > fabs(delta.y))
		*progress = 2;
}
