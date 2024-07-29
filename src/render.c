/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:07 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:50:26 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_matr_final:
Computes the final rotation matrix by combining individual rotation matrices.
This function creates a composite rotation matrix that represents all rotations
(around x, y, and z axes) applied to the map.
Math: Multiplies rotation matrices in the order: Z * Y * X (yaw * pitch * roll)
R = Rz(γ) * Ry(β) * Rx(α), where α, β, γ are rotation angles
around x, y, z axes respectively.
// Called from:
ft_apply_transformations
// Output:
Returns the final 3x3 rotation matrix combining all rotations.*/
t_matrix	ft_matr_final(t_mlx *fdf)
{
	t_matrix	roll;
	t_matrix	pitch;
	t_matrix	yaw;
	t_matrix	temp;
	t_matrix	rslt;

	roll = ft_matr_rot_x(fdf->cam->alpha);
	pitch = ft_matr_rot_y(fdf->cam->beta);
	yaw = ft_matr_rot_z(fdf->cam->gamma);
	temp = ft_matr_mult(pitch, roll);
	rslt = ft_matr_mult(yaw, temp);
	return (rslt);
}

/* ft_rotate:
Applies a rotation matrix to a point.
This function transforms a point's coordinates using the given rotation matrix.
Math: Multiplies the point's coordinates by the rotation matrix:
[x']   [r11 r12 r13]   [x]
[y'] = [r21 r22 r23] * [y]
[z']   [r31 r32 r33]   [z]
// Called from:
ft_apply_transformations
// Output:
Modifies the input point's x, y, and z coordinates based on the rotation.*/
void	ft_rotate(t_matrix rot, t_pnt *p)
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

/* ft_apply_transformations:
Applies all transformations (scale, rotation, spin) to a point.
This function orchestrates the complete transformation process for each point.
Steps: 1. Apply scaling
       2. Apply combined rotation (from ft_matr_final)
       3. Apply additional spin rotation around z-axis
Math: For spin, applies 2D rotation:
x' = x * cos(θ) - y * sin(θ)
y' = x * sin(θ) + y * cos(θ)
Where θ is the spin angle.
// Called from:
ft_render
// Output:
Modifies the input point's coordinates based on all current transformations.*/
void	ft_apply_transformations(t_pnt *p, t_mlx *fdf)
{
	t_matrix	final_rot;
	double		cos_spin;
	double		sin_spin;
	double		x;
	double		y;

	p->x *= fdf->cam->theta;
	p->y *= fdf->cam->theta;
	p->z *= fdf->cam->z_move;
	final_rot = ft_matr_final(fdf);
	ft_rotate(final_rot, p);
	cos_spin = cos(fdf->cam->spin_angle);
	sin_spin = sin(fdf->cam->spin_angle);
	x = p->x;
	y = p->y;
	p->x = x * cos_spin - y * sin_spin;
	p->y = x * sin_spin + y * cos_spin;
}

/* ft_render:
Prepares a point for rendering by applying all transformations and projections.
This function is the main pipeline for converting a 3D map point to its
2D screen position.
Steps: 1. Apply all transformations
       2. Apply selected projection
       3. Adjust for camera position (x_move, y_move)
       4. Clip coordinates to prevent rendering outside the window
// Called from:
ft_draw_points
// Output:
Modifies the input point's coordinates to its final screen position,
ready for drawing.*/
void	ft_render(t_pnt *p, t_mlx *fdf)
{
	ft_apply_transformations(p, fdf);
	p->depth = 0;
	if (fdf->cam->proj == PROJ_ISO)
		ft_iso_proj(p);
	else if (fdf->cam->proj == PROJ_1PT)
		ft_one_point_proj(p, fdf->cam);
	else if (fdf->cam->proj == PROJ_2PTS)
		ft_two_point_proj(p, fdf->cam);
	else if (fdf->cam->proj == PROJ_ORTHO)
		ft_ortho_proj(p);
	if (isinf(p->x) || isinf(p->y))
	{
		p->x = INFINITY;
		p->y = INFINITY;
		return ;
	}
	p->x += fdf->cam->x_move;
	p->y += fdf->cam->y_move;
	p->x = fmax(fmin(p->x, WIN_WIDTH * 2), -WIN_WIDTH);
	p->y = fmax(fmin(p->y, WIN_HEIGHT * 2), -WIN_HEIGHT);
}
