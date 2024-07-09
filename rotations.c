/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:27 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/09 16:37:20 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix ft_rotation_x(double alpha)
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
	return(roll);
}

t_matrix ft_rotation_y(double beta)
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
	return(pitch);
}

t_matrix ft_rotation_z(double gamma)
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
	return(yaw);
}