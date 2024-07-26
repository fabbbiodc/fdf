/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:32:28 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/26 08:53:37 by fdi-cecc         ###   ########.fr       */
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

typedef struct s_zoom
{
	t_point	min;
	t_point	max;
	double	scale_x;
	double	scale_y;
	double	scale_z;
	double	scale;
}	t_zoom;

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
	int 	projection;
	double	x_move;
	double 	y_move;
	double 	alpha;
	double 	beta;
	double 	gamma;
	double 	theta;
	double 	z_move;
	double 	scale_x;
	double 	scale_y;
	double 	map_width;
    double 	map_height;
    double 	map_depth;
	int		fitted;
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