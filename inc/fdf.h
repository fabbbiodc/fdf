/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:23:18 by fdi-cecc         ###   ########.fr       */
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
t_mlx		*ft_fdf_allocate(void);
int			ft_argcheck(int argc);
void		ft_set_hooks(t_mlx *fdf);

// cam

void		ft_cam_limits(t_mlx *fdf, t_pnt *min, t_pnt *max);
void		ft_init_limits(t_bound *bounds);
void		ft_init_point(t_pnt *point, int value);
void		ft_cam_fit(t_mlx *fdf);
void		ft_cam_params(t_mlx *fdf);

//controls

int			ft_is_control_key(int key);
void		ft_handle_zoom(int key, t_mlx *fdf);
void		ft_handle_move(int key, t_mlx *fdf);
void		ft_cam_control(int key, t_mlx *fdf);
void		ft_toggle_projection(t_mlx *fdf);

// parse

int			ft_color(char *z);
void		ft_set_point(t_pnt *p, int i, int y, char *z);
int			ft_parse_line(char *line, t_pnt *p, int y, int width);
int			ft_parse_loop(t_map *map, int fd);
t_map		*ft_parse_map(char *map_file);

// map

int			ft_map_rows(t_map *map);
t_map		*ft_map_allocate(int width, int height);
int			ft_map_size(char *map, int *width, int *height);
void		ft_map_free(t_map *map);
t_map		*ft_map_process(char *map_file);

// drawline

void		ft_draw_points(t_mlx *fdf, int y, int x);
int			ft_get_color(t_mlx *fdf, t_pnt *point);
int			ft_draw(t_mlx *fdf);
void		ft_putpixel(t_mlx *fdf, int x, int y, int color);

// dda

void		ft_dda(t_mlx *fdf, t_pnt *p1, t_pnt *p2);
void		ft_dda_loop(t_mlx *fdf, t_pnt *crnt, t_pnt *p1, t_pnt *p2);
void		ft_update_current(t_pnt *crnt, t_pnt *p1, t_pnt *p2, double *prog);

// free

void		ft_free_split(char **points);
int			ft_free(t_mlx *fdf);
void		ft_cleanup_mlx(t_mlx *fdf);
int			ft_terminate(t_mlx *fdf);

// render

void		ft_render(t_pnt *p, t_mlx *fdf);
void		ft_scale(t_pnt *p, t_cam *cam);
void		ft_center(t_pnt *p, t_cam *cam);
void		ft_rotate(t_matrix rot, t_pnt *p);
void		ft_apply_transformations(t_pnt *p, t_mlx *fdf);

// rotations

t_matrix	ft_matr_rot_x(double alpha);
t_matrix	ft_matr_rot_y(double beta);
t_matrix	ft_matr_rot_z(double gamma);
t_matrix	ft_matr_mult(t_matrix a, t_matrix b);
t_matrix	ft_matr_final(t_mlx *fdf);

// color

int			ft_color_shift(int color, int shift);
int			ft_color_process(int start, int end, double percentage);
int			ft_fade_color(int color, double depth, double max_depth);
int			ft_color_gradient(int start, int end, double percentage);
void		ft_toggle_color(t_mlx *fdf);

// init

int			ft_fdf_init(t_mlx *fdf, char *map_file);
int			ft_init_image(t_mlx *fdf);

// panel

void		ft_blend_colors(t_mlx *fdf, int pixel, int color, int alpha);
int			ft_calculate_blend(int src_color, int dst_color, int alpha);
void		ft_pnl_txt(t_mlx *fdf, t_pnt *p, char *str, int color);
void		ft_panel_logo(t_mlx *fdf, int x, int y);
const char	*ft_get_color_name(int color_scheme);
void		ft_panel_content(t_mlx *fdf);
void		ft_display_map_info(t_mlx *fdf, t_pnt *p);
void		ft_display_controls(t_mlx *fdf, t_pnt *p);
const char	*ft_get_projection_name(int proj);
void		ft_panel_draw(t_mlx *fdf);

// projections

void		ft_apply_projection(t_pnt *temp, t_mlx *fdf);
void		ft_two_point_proj(t_pnt *p, t_cam *cam);
void		ft_ortho_proj(t_pnt *p);
void		ft_one_point_proj(t_pnt *p, t_cam *cam);
void		ft_iso_proj(t_pnt *p);

// placement

void		ft_update_limits(t_pnt *p, t_pnt *min, t_pnt *max);
void		ft_update_map_limits(t_pnt *temp, t_bound *bounds);
void		ft_center_map(t_mlx *fdf);

#endif