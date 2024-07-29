/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:12:44 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:46:04 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_apply_projection:
Applies the currently selected projection to a point.
This function serves as a dispatcher, calling the appropriate projection function
based on the current projection mode stored in the camera settings.
// Called from:
ft_center_map, ft_render
// Output:
Modifies the input point's coordinates according to the selected projection.*/
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
Isometric projection is a method of visually representing 3D objects in 2D.
It uses a 30-degree angle from the horizontal, creating a pseudo-3D effect.
Math: The transformation is achieved using these formulas:
    x_iso = (x - y) * cos(30°)
    y_iso = (x + y) * sin(30°) - z
Where 30° is approximately 0.523599 radians (often stored as RAD_30 constant).
// Called from:
ft_apply_projection
// Output:
Modifies the input point's x and y coordinates to their isometric projection.*/
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
This projection creates the illusion of depth by having parallel lines 
onverge to a single vanishing point.
Math: The transformation involves these steps:
1. Apply isometric-like rotation (usually 30° around x-axis).
2. Apply perspective division:
    x' = (x * distance) / (z + distance)
    y' = (y * distance) / (z + distance)
Where 'distance' is the distance from the viewer to the projection plane.
// Called from:
ft_apply_projection
// Output:
Modifies the point's x, y coordinates and sets its depth
for perspective effect.*/
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
This projection uses two vanishing points, typically on the horizon line,
creating a more dynamic 3D effect.
Math: Similar to one-point, but with an additional transformation:
1. Apply isometric-like rotation.
2. Apply perspective division as in one-point projection.
3. Apply additional horizontal shift based on y-coordinate:
    x' = x - (y / 4)  // The division by 4 is an arbitrary factor for effect
// Called from:
ft_apply_projection
// Output:
Modifies the point's x, y coordinates and sets its depth for a more
pronounced perspective effect.*/
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
Orthographic projection represents 3D objects in 2D
by projecting points to a plane along parallel lines.
Math: In this implementation, it appears to
simply invert the z-axis and apply a 180° rotation around the x-axis:
1. z = -z
2. Apply rotation matrix for 180° around x-axis:
    [1     0      0]
    [0  cos θ -sin θ]
    [0  sin θ  cos θ]
Where θ is 180° or π radians.
// Called from:
ft_apply_projection
// Output:
Modifies the point's coordinates to create a top-down orthographic view.*/
void	ft_ortho_proj(t_pnt *p)
{
	t_matrix	iso_rot;

	iso_rot = ft_matr_rot_x(RAD_180);
	ft_rotate(iso_rot, p);
	p->z = -p->z;
}
