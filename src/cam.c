/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:05:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/30 10:18:02 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_cam_limits:
Calculates the minimum and maximum coordinates of the map after
applying current transformations.
// Process:
1. Iterates through all points in the map (nested loops for height and width)
2. For each point:
   a. Copies the original point data
   b. Applies scaling: multiplies x and y by theta, z by z_move
   c. Applies current projection (e.g., isometric) using ft_iso_proj
   d. Updates min and max values using ft_update_limits
      - If current x < min.x, updates min.x
      - If current y < min.y, updates min.y
      - If current x > max.x, updates max.x
      - If current y > max.y, updates max.y
3. After processing all points, min and max contain the map's boundaries
// Key aspect:
This function doesn't modify the original map data; it only calculates boundaries
// Called from:
ft_cam_fit
// Output:
Updates min and max point structures with the map's boundaries
in screen space*/
void	ft_cam_limits(t_mlx *fdf, t_pnt *min, t_pnt *max)
{
	int		i;
	int		j;
	t_pnt	p;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			p = fdf->map->points[i][j];
			p.x *= fdf->cam->theta;
			p.y *= fdf->cam->theta;
			p.z *= fdf->cam->z_move;
			ft_iso_proj(&p);
			ft_update_limits(&p, min, max);
			j++;
		}
		i++;
	}
}

/* ft_init_limits:
Initializes the boundary structure with extreme values.
// Called from:
ft_center_map
// Output:
Modifies the bounds structure directly.*/
void	ft_init_limits(t_bound *bounds)
{
	bounds->min_x = INFINITY;
	bounds->max_x = -INFINITY;
	bounds->min_y = INFINITY;
	bounds->max_y = -INFINITY;
}

/* ft_init_point:
Initializes all components of a point structure with a given value.
// Called from:
ft_cam_fit
// Output:
Modifies the point structure directly.*/
void	ft_init_point(t_pnt *point, int value)
{
	point->x = value;
	point->y = value;
	point->z = value;
	point->color = value;
	point->depth = value;
}

/* ft_cam_fit:
Adjusts the camera parameters to fit the entire map within the window.
// Process:
1. Starts with a large scale (theta) of 40.0
2. Enters a loop that continues while scale > 0.1:
   a. Sets camera theta to current scale
   b. Sets z_move to half of theta (balances vertical scaling)
   c. Calls ft_cam_limits to get map boundaries at this scale
   d. Checks if map width and height fit within window (with margins):
      - If fits, breaks the loop
      - If doesn't fit, reduces scale by 5% (multiplies by 0.95)
3. After finding suitable scale or reaching minimum:
   a. Sets 'fitted' flag to prevent unnecessary refitting
   b. Calls ft_center_map to position the scaled map
// Key aspect:
Uses iterative approach to find optimal scale, balancing map size and visibility
// Called from:
ft_fdf_init
// Output:
Updates camera parameters (theta, z_move) for optimal map display
Ensures entire map is visible within the window*/
void	ft_cam_fit(t_mlx *fdf)
{
	t_pnt	min;
	t_pnt	max;
	double	scale;

	if (fdf->cam->fitted)
		return ;
	scale = 40.0;
	while (scale > 0.1)
	{
		ft_init_point(&min, INT_MAX);
		ft_init_point(&max, INT_MIN);
		fdf->cam->theta = scale;
		fdf->cam->z_move = scale * 0.5;
		ft_cam_limits(fdf, &min, &max);
		if (max.x - min.x < WIN_WIDTH - 2 * MARGIN
			&& max.y - min.y < WIN_HEIGHT - 2 * MARGIN)
			break ;
		scale *= 0.95;
	}
	fdf->cam->fitted = 1;
	ft_center_map(fdf);
}

/* ft_cam_params:
Initializes or resets all camera parameters to their default values.
// Process:
1. Sets projection mode (e.g., PROJ_ISO for isometric)
2. Initializes rotation angles (alpha, beta, gamma) to 0
3. Sets initial scale (theta) to 1
4. Sets z_move (vertical scaling) to a small value (e.g., 0.1)
5. Resets 'fitted' flag to 0
6. Sets default projection distance for perspective projections
7. Initializes spin angle to 0
8. Sets initial color scheme
// Key aspect:
Provides a consistent starting point for camera settings
// Called from:
ft_cam_init, ft_fdf_init
// Output:
Initializes the camera structure with default values,
preparing it for initial rendering and subsequent user interactions*/
void	ft_cam_params(t_mlx *fdf)
{
	fdf->cam->proj = PROJ_ISO;
	fdf->cam->alpha = 0;
	fdf->cam->beta = 0;
	fdf->cam->gamma = 0;
	fdf->cam->theta = 1;
	fdf->cam->z_move = 0.1;
	fdf->cam->fitted = 0;
	fdf->cam->proj_distance = 1000.0;
	fdf->cam->spin_angle = 0;
	fdf->cam->color_scheme = 0;
	ft_cam_fit(fdf);
}
