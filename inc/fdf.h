/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/28 01:01:32 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <mlx.h>
# include <limits.h>
# include "keys.h"
# include "structs.h"
# include "variables.h"
# include "../libft/libft.h"

// fdf

int			ft_keyreact(int key, t_mlx *fdf);
int			ft_abs(int n);
int			ft_img_refresh(t_mlx *fdf);

// cam

int			ft_cam_init(t_mlx *fdf);
void		ft_cam_control(int key, t_mlx *fdf);
void		ft_cam_params(t_mlx *fdf);
void		ft_cam_fit(t_mlx *fdf);
void		ft_toggle_projection(t_mlx *fdf);

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
void		ft_pixel_increment(t_mlx *fdf, t_point *current);


// error

int			ft_error_handle(int errorcode);
int			ft_terminate(t_mlx *fdf);
int			ft_free(t_mlx *fdf);
void		ft_free_split(char **points);

// render

void		ft_iso_proj(t_point *p);
void		ft_render(t_point *p, t_mlx *fdf);
void		ft_scale(t_point *p, t_cam *cam);
void		ft_center(t_point *p, t_cam *cam);
void		ft_rotate(t_matrix rot, t_point *p);
void		ft_one_point_proj(t_point *p, t_cam *cam);

// rotations

t_matrix	ft_matr_rot_x(double alpha);
t_matrix	ft_matr_rot_y(double beta);
t_matrix	ft_matr_rot_z(double gamma);
t_matrix	ft_matr_mult(t_matrix a, t_matrix b);
t_matrix	ft_matr_final(t_mlx *fdf);

// color

int			ft_color_gradient(int start_color, int end_color, double percentage);
int 		ft_fade_color(int color, double depth, double max_depth);

// init

int			ft_fdf_init(t_mlx *fdf, char *map_file);
int			ft_init_image(t_mlx *fdf);
int 		ft_panel_init(t_mlx *fdf);

// panel

void	ft_panel_draw(t_mlx *fdf);
void	ft_panel_logo(t_mlx *fdf, int x, int y);
void    ft_toggle_color(t_mlx *fdf);
int     ft_get_color(t_mlx *fdf);
const char    *ft_get_color_name(int color_scheme);
const char *ft_get_projection_name(int projection);

#endif