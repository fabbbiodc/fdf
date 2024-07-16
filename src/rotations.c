/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:27 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/14 19:59:38 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_matrix	ft_matr_mult(t_matrix a, t_matrix b)
{
	t_matrix	rslt;
	int			i;
	int			j;
	int			k;

	ft_memset(&rslt, 0, sizeof(t_matrix));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				rslt.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (rslt);
}

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