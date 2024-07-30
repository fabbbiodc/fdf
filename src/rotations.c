/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:27 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/30 09:28:37 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_matr_rot_x:
Creates a rotation matrix for rotation around the X-axis.
// Math:
Generates a 3x3 matrix for rotation by angle α (alpha):
[1    0        0    ]
[0    cos(α)  -sin(α)]
[0    sin(α)   cos(α)]
// Process:
1. Calculates sin(α) and cos(α)
2. Fills the matrix with appropriate values
3. Sets 1 for the x-axis elements as x doesn't change in x-rotation
// Called from:
ft_matr_final, ft_one_point_proj, ft_two_point_proj
// Output:
Returns a t_matrix structure representing the X-axis rotation*/
t_matrix	ft_matr_rot_x(double alpha)
{
	t_matrix	roll;
	double		sin_a;
	double		cos_a;

	sin_a = sin(alpha);
	cos_a = cos(alpha);
	ft_memset(&roll, 0, sizeof(t_matrix));
	roll.matrix[0][0] = 1;
	roll.matrix[1][1] = cos_a;
	roll.matrix[1][2] = -sin_a;
	roll.matrix[2][1] = sin_a;
	roll.matrix[2][2] = cos_a;
	return (roll);
}

/* ft_matr_rot_y:
Creates a rotation matrix for rotation around the Y-axis.
// Math:
Generates a 3x3 matrix for rotation by angle β (beta):
[ cos(β)   0   sin(β)]
[   0      1     0   ]
[-sin(β)   0   cos(β)]
// Process:
1. Calculates sin(β) and cos(β)
2. Fills the matrix with appropriate values
3. Sets 1 for the y-axis elements as y doesn't change in y-rotation
// Called from:
ft_matr_final
// Output:
Returns a t_matrix structure representing the Y-axis rotation*/
t_matrix	ft_matr_rot_y(double beta)
{
	t_matrix	pitch;
	double		sin_b;
	double		cos_b;

	sin_b = sin(beta);
	cos_b = cos(beta);
	ft_memset(&pitch, 0, sizeof(t_matrix));
	pitch.matrix[0][0] = cos_b;
	pitch.matrix[0][2] = sin_b;
	pitch.matrix[1][1] = 1;
	pitch.matrix[2][0] = -sin_b;
	pitch.matrix[2][2] = cos_b;
	return (pitch);
}

/* ft_matr_rot_z:
Creates a rotation matrix for rotation around the Z-axis.
// Math:
Generates a 3x3 matrix for rotation by angle γ (gamma):
[cos(γ)  -sin(γ)   0]
[sin(γ)   cos(γ)   0]
[  0        0      1]
// Process:
1. Calculates sin(γ) and cos(γ)
2. Fills the matrix with appropriate values
3. Sets 1 for the z-axis elements as z doesn't change in z-rotation
// Called from:
ft_matr_final
// Output:
Returns a t_matrix structure representing the Z-axis rotation*/
t_matrix	ft_matr_rot_z(double gamma)
{
	t_matrix	yaw;
	double		sin_g;
	double		cos_g;

	sin_g = sin(gamma);
	cos_g = cos(gamma);
	ft_memset(&yaw, 0, sizeof(t_matrix));
	yaw.matrix[0][0] = cos_g;
	yaw.matrix[0][1] = -sin_g;
	yaw.matrix[1][0] = sin_g;
	yaw.matrix[1][1] = cos_g;
	yaw.matrix[2][2] = 1;
	return (yaw);
}

/* ft_matr_mult_helper:
Helper function to perform matrix multiplication for a single row.
// Math:
Calculates the dot product of a row from matrix A with columns from matrix B.
result[i][j] = Σ(A[i][k] * B[k][j]) for k = 0 to 2
// Process:
1. Iterates over columns of the result matrix
2. For each element, computes the dot product of row i of A with column j of B
// Called from:
ft_matr_mult
// Output:
Modifies the result matrix, filling in one row of the multiplication result*/
void	ft_matr_mult_helper(t_matrix *rslt, t_matrix a, t_matrix b, int i)
{
	int	j;
	int	k;

	j = 0;
	while (j < 3)
	{
		k = 0;
		while (k < 3)
		{
			rslt->matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
			k++;
		}
		j++;
	}
}

/* ft_matr_mult:
Performs multiplication of two 3x3 matrices.
// Math:
Computes the product of matrices A and B:
C[i][j] = Σ(A[i][k] * B[k][j]) for k = 0 to 2
// Process:
1. Initializes result matrix to zero
2. Iterates over rows of the result matrix
3. Calls ft_matr_mult_helper for each row to compute values
// Key aspect:
This operation combines two transformations into a single matrix
// Called from:
ft_matr_final
// Output:
Returns a new t_matrix structure representing the
product of the input matrices*/
t_matrix	ft_matr_mult(t_matrix a, t_matrix b)
{
	t_matrix	rslt;
	int			i;

	ft_memset(&rslt, 0, sizeof(t_matrix));
	i = 0;
	while (i < 3)
	{
		ft_matr_mult_helper(&rslt, a, b, i);
		i++;
	}
	return (rslt);
}
