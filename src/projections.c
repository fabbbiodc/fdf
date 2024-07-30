/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:12:44 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/30 09:31:29 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_apply_projection:
Applies the currently selected projection to a point.
// Process:
1. Checks the current projection mode (fdf->cam->proj)
2. Calls the appropriate projection function based on the mode:
   - PROJ_ISO: ft_iso_proj
   - PROJ_1PT: ft_one_point_proj
   - PROJ_2PTS: ft_two_point_proj
   - PROJ_ORTHO: ft_ortho_proj
// Key aspect:
Acts as a dispatcher for different projection methods
// Called from:
ft_center_map, ft_render
// Output:
Modifies the input point's coordinates according to the selected projection*/
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

/* ft_iso_proj:
Applies isometric projection to a point.
// Math:
Transforms 3D coordinates (x, y, z) to 2D isometric view (x', y'):
x' = (x - y) * cos(30°)
y' = (x + y) * sin(30°) - z
Where 30° is approximately 0.523599 radians (often stored as RAD_30 constant)
// Process:
1. Calculates new x coordinate (x_iso)
2. Calculates new y coordinate (y_iso)
3. Updates the point's x and y with these new values
// Key aspect:
Creates a pseudo-3D view without perspective
// Called from:
ft_apply_projection
// Output:
Modifies the input point's x and y coordinates to their isometric projection*/
void	ft_iso_proj(t_pnt *p)
{
	double	x_iso;
	double	y_iso;

	x_iso = (p->x - p->y) * cos(RAD_30);
	y_iso = ((p->x + p->y) * sin(RAD_30)) - p->z;
	p->x = x_iso;
	p->y = y_iso;
}

/* ft_one_point_proj:
Applies one-point perspective projection to a point.
// Math:
Applies perspective division after rotating the point:
1. Rotate point (usually 30° around x-axis for isometric-like view)
2. Apply perspective division:
   x' = (x * distance) / (z + distance)
   y' = (y * distance) / (z + distance)
Where 'distance' is the distance from the viewer to the projection plane
// Process:
1. Rotates the point using an isometric-like rotation matrix
2. Inverts z (to make objects further away appear higher)
3. Calculates z_persp (z + projection distance)
4. Applies perspective division to x and y
5. Stores original z as 'depth' for potential depth-based effects
// Key aspect:
Creates a basic perspective effect with a single vanishing point
// Called from:
ft_apply_projection
// Output:
Modifies the point's x, y coordinates and sets its depth
for perspective effect*/
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

/* ft_two_point_proj:
Applies two-point perspective projection to a point.
// Math:
Similar to one-point, but with an additional horizontal shift:
1. Apply steps 1-4 from one-point projection
2. Apply additional horizontal shift: x' = x - (y / 4)
The division by 4 is an arbitrary factor to control the effect strength
// Process:
1. Performs steps similar to one-point projection
2. Adds an extra calculation to shift x based on y
// Key aspect:
Creates a more dynamic perspective effect with two vanishing points
// Called from:
ft_apply_projection
// Output:
Modifies the point's x, y coordinates and sets its depth for a more
pronounced perspective effect*/
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

/* ft_ortho_proj:
Applies orthographic projection to a point.
// Math:
Simply inverts the z-axis and applies a 180° rotation around the x-axis:
1. z = -z
2. Apply rotation matrix for 180° around x-axis:
   [1     0      0]
   [0  cos θ -sin θ]
   [0  sin θ  cos θ]
Where θ is 180° or π radians
// Process:
1. Inverts the z coordinate
2. Applies a 180° rotation around the x-axis using a rotation matrix
// Key aspect:
Provides a top-down view of the object without perspective
// Called from:
ft_apply_projection
// Output:
Modifies the point's coordinates to create a top-down orthographic view*/
void	ft_ortho_proj(t_pnt *p)
{
	t_matrix	iso_rot;

	iso_rot = ft_matr_rot_x(RAD_180);
	ft_rotate(iso_rot, p);
	p->z = -p->z;
}
