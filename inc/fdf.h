/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/15 17:05:41 by fdi-cecc         ###   ########.fr       */
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

// fdf

int				ft_keyreact(int key, t_mlx *fdf);
int				ft_abs(int n);
void			ft_definepoint(t_point *point, double x, double y, double z);
int				ft_init_image(t_mlx *fdf);

// cam

int				ft_cam_init(t_mlx *fdf);
void			ft_cam_rotate(int key, t_mlx *fdf);
void			ft_cam_params(t_mlx *fdf);

// map

static int		ft_map_size(char *map, int *width, int *height);
t_map			ft_map_parse(char *map);

// drawline

void			ft_putpixel(t_mlx *mlx, int x, int y, int color);
void			ft_dda(t_mlx *fdf, t_point *p1, t_point *p2);
int				ft_draw(t_mlx *fdf);
int				ft_img_refresh(t_mlx *fdf);

// error

int				ft_error_handle(int errorcode);
int				ft_terminate(t_mlx *fdf);
int				ft_free(t_mlx *fdf);

// utils

void			*ft_memset(void *str, int c, size_t n);
static size_t	ft_words(const char *s, char c);

// render

void			ft_iso_proj(t_point *p);
void			ft_render(t_point *p, t_mlx *fdf);
void			t_center(t_point *p, double x_move, double y_move);

// rotations

t_matrix		ft_matr_rot_x(double alpha);
t_matrix		ft_matr_rot_y(double beta);
t_matrix		ft_matr_rot_z(double gamma);
t_matrix		ft_matr_mult(t_matrix a, t_matrix b);
t_matrix		ft_matr_final(t_mlx *fdf);

// get_next_line
char			*get_next_line(int fd);
void			ft_newlist(t_list **list, int fd);
void			ft_append(t_list **list, char *buffer);
char			*ft_getline(t_list *list);
void			ft_cleanlist(t_list **list);

// get_next_line_utils

int				ft_newline(t_list *list);
t_list			*ft_lastnode(t_list *list);
int				ft_linelength(t_list *list);
void			ft_copyline(t_list *list, char *str);
void			ft_freelist(t_list **list, t_list *cleannode, char *buffer);

#endif