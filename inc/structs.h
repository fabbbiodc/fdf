/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:32:28 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 18:41:49 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_bound
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
}	t_bound;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	color;
	double	depth;
}	t_pnt;

typedef struct s_map
{
	int		width;
	int		height;
	t_pnt	**points;
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
	int		proj;
	double	x_move;
	double	y_move;
	double	alpha;
	double	beta;
	double	gamma;
	double	theta;
	double	z_move;
	int		fitted;
	double	proj_distance;
	double	spin_angle;
	int		color_scheme;
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