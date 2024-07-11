/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/11 16:10:58 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LINE_H
# define	LINE_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<math.h>
# include	<unistd.h> // remove
# include	"keys.h"
# include	"structs.h"
# include	"variables.h"
# include	"minilibx_linux/mlx.h"

//fdf.c

int 		ft_keyreact(int key, t_mlx *fdf);
int 		ft_abs(int n);
void 		ft_definepoint(t_point *point, double x, double y, double z);
int			ft_init_image(t_mlx *fdf);

// drawline.c

t_point		*ft_direction(t_point *p1, t_point *p2);
void		ft_nextpix(int error[2], t_point *delta, t_point *current, t_point *direction);
void		ft_putpixel(t_mlx *mlx, int x, int y, int color);
void		ft_dda(t_mlx *fdf, t_point *p1, t_point *p2);
int			ft_draw(t_mlx *fdf);

// error.c

int			ft_error_handle(int errorcode);
int			ft_terminate(t_mlx *fdf);
int			ft_free(t_mlx *fdf);

// utils.c

int			ft_abs(int n);
void		*ft_memset(void *str, int c, size_t n);


//render.c

void 		ft_iso_proj(t_point *p);
void		ft_render(t_point *p, t_mlx *fdf);
void		ft_cam_rotate(int key, t_mlx *fdf);
void 		ft_cam_params(t_mlx *fdf);
int			ft_img_refresh(t_mlx *fdf);
int			ft_cam_init(t_mlx *fdf);
void 		ft_center(t_point *p, double x_move, double y_move);

//rotations.c

t_matrix	ft_matr_rot_x(double alpha);
t_matrix 	ft_matr_rot_y(double beta);
t_matrix	ft_matr_rot_z(double gamma);
t_matrix 	ft_matr_mult(t_matrix a, t_matrix b);
t_matrix	ft_matr_final(t_mlx *fdf);

#endif
