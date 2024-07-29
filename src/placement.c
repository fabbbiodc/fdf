/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:03:41 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:36:19 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_update_limits(t_pnt *p, t_pnt *min, t_pnt *max)
{
	min->x = fmin(min->x, p->x);
	min->y = fmin(min->y, p->y);
	max->x = fmax(max->x, p->x);
	max->y = fmax(max->y, p->y);
}

void	ft_center_map(t_mlx *fdf)
{
	int		i;
	int		j;
	t_bound	bounds;
	t_pnt	temp;

	ft_init_limits(&bounds);
	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			temp = fdf->map->points[i][j];
			ft_apply_transformations(&temp, fdf);
			ft_apply_projection(&temp, fdf);
			ft_update_map_limits(&temp, &bounds);
			j++;
		}
		i++;
	}
	fdf->cam->x_move = WIN_WIDTH / 2 - (bounds.min_x + bounds.max_x) / 2;
	fdf->cam->y_move = WIN_HEIGHT / 2 - (bounds.min_y + bounds.max_y) / 2;
}

void	ft_update_map_limits(t_pnt *temp, t_bound *bounds)
{
	if (!isinf(temp->x) && !isinf(temp->y))
	{
		bounds->min_x = fmin(bounds->min_x, temp->x);
		bounds->max_x = fmax(bounds->max_x, temp->x);
		bounds->min_y = fmin(bounds->min_y, temp->y);
		bounds->max_y = fmax(bounds->max_y, temp->y);
	}
}
