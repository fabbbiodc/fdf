/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/23 15:46:41 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <mlx.h>
# include "keys.h"
# include "structs.h"
# include "variables.h"
# include "../libft/libft.h"

// fdf

int			ft_keyreact(int key, t_mlx *fdf);
int			ft_abs(int n);
int			ft_init_image(t_mlx *fdf);
int			ft_img_refresh(t_mlx *fdf);

// cam

int			ft_cam_init(t_mlx *fdf);
void		ft_cam_rotate(int key, t_mlx *fdf);
void		ft_cam_params(t_mlx *fdf);

// parse

t_map		*ft_parse_map(char *map);
int			ft_parse_line(char *line, t_point *p, int y, int width);
int			ft_color(char *z);

// map

t_map		*ft_map_process(char *map_file);
void		ft_map_free(t_map *map);
// static int	ft_map_size(char *map, int *width, int *height);
// static t_map	*ft_map_allocate(int width, int height);
// static int	ft_map_rows(t_map *map);

// drawline

void		ft_putpixel(t_mlx *mlx, int x, int y, int color);
void		ft_dda(t_mlx *fdf, t_point *p1, t_point *p2);
int			ft_draw(t_mlx *fdf);
void		ft_draw_points(t_mlx *fdf, int y, int x);
void		ft_definepoint(t_point *p, int x, int y, int z);

// error

int			ft_error_handle(int errorcode);
int			ft_terminate(t_mlx *fdf);
int			ft_free(t_mlx *fdf);
void		ft_free_split(char **points);

// render

void		ft_iso_proj(t_point *p);
void		ft_render(t_point *p, t_mlx *fdf);
void		ft_center(t_point *p, double x_move, double y_move);

// rotations

t_matrix	ft_matr_rot_x(double alpha);
t_matrix	ft_matr_rot_y(double beta);
t_matrix	ft_matr_rot_z(double gamma);
t_matrix	ft_matr_mult(t_matrix a, t_matrix b);
t_matrix	ft_matr_final(t_mlx *fdf);

#endif