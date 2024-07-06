/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/06 17:35:47 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LINE_H
# define	LINE_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<math.h>
# include	"keys.h"
# include	"structs.h"
# include	"variables.h"
# include	"minilibx_linux/mlx.h"

//fdf.c

int 	ft_keyreact(int key, t_mlx *fdf);
int 	ft_abs(int n);
void 	ft_definepoint(t_point *point, int x, int y, int z);
int		ft_init_image(t_mlx *fdf);

// drawline.c

t_point	*ft_direction(t_point *p1, t_point *p2);
void	ft_nextpix(int error[2], t_point *delta, t_point *current, t_point *direction);
void	ft_putpixel(t_mlx *mlx, int x, int y, int color);
void	ft_bresenham(t_mlx *fdf, t_point *p1, t_point *p2);
int		ft_draw(t_mlx *fdf);

// error.c

int		ft_error_handle(int errorcode);
int		ft_terminate(t_mlx *fdf);
int		ft_free(t_mlx *fdf);

// utils.c

int	ft_abs(int n);

//projections.c

void ft_iso_proj(t_point *p);

#endif
