/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:32:28 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/16 18:20:28 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}	t_map;

typedef struct s_img
{
	char	*addr;
	int		bpp;
	int		linesize;
	int		endian;
}	t_img;

typedef struct s_cam
{
	int		projection;
	double	theta;
	double	alpha;
	double	beta;
	double	gamma;
	double	x_move;
	double	y_move;
}	t_cam;

typedef struct s_matrix
{
	double	matrix[3][3];
}	t_matrix;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	t_img	*img_att;
	t_cam	*cam;
	t_map	*map;
}	t_mlx;

#endif