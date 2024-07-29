/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:03:41 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:37:36 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_update_limits:
Updates the minimum and maximum coordinates based on a given point.
This function is crucial for determining the overall boundaries of the map.
It compares the x and y coordinates of the given point
with the current min and max,
updating them if the point extends beyond the current limits.
// Called from:
ft_cam_limits
// Output:
Modifies min and max point structures to encompass the given point,
effectively expanding the known boundaries of the map.*/
void	ft_update_limits(t_pnt *p, t_pnt *min, t_pnt *max)
{
	min->x = fmin(min->x, p->x);
	min->y = fmin(min->y, p->y);
	max->x = fmax(max->x, p->x);
	max->y = fmax(max->y, p->y);
}

/* ft_center_map:
Calculates the offset needed to center the map in the window.
This function iterates through all points of the map, applying current
transformations and projections to determine the map's extent in screen space.
It then calculates the difference between the map's center and
the window's center
to determine the necessary offset for centering.
// Called from:
ft_cam_fit, ft_toggle_projection
// Output:
Updates the camera's x_move and y_move values in the fdf structure,
which will be used in rendering to position the map at the
center of the window.*/
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

/* ft_update_map_limits:
Updates the boundaries of the map based on a transformed point.
Similar to ft_update_limits, but specifically for use within ft_center_map.
It checks if the point is valid (not infinity) before updating the bounds.
This function helps in determining the actual screen space occupied by the map
after all transformations and projections have been applied.
// Called from:
ft_center_map
// Output:
Modifies the bounds structure to include the given point, if valid.
This gradually builds up a picture of the map's extent in screen space.*/
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
