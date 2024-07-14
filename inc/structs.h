/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:32:28 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/14 20:58:37 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	double		color;
	double		len;
}	t_point;

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
	t_point	**points;
	int		map_height;
	int		map_width;
}	t_mlx;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

#endif