/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/03 22:26:04 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LINE_H
# define	LINE_H

# include	<stdio.h>
# include	<stdlib.h>
# include	"keys.h"
# define	WIN_HEIGHT 500
# define	WIN_WIDTH 500
# define	COLOR 0x00FF0000

typedef	struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	int		len;
}	t_point;

typedef struct s_img
{
	char	*addr;
	int		bpp;
	int		linesize;
	int		endian;
}	t_img;

typedef	struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	t_img	*img_att;
}	t_mlx;

//fdf.c

int 	ft_keyreact(int key, t_mlx *fdf);
int 	ft_abs(int n);
void 	ft_definepoint(t_point *point, int x, int y);
int		ft_draw(t_mlx *fdf);

// drawline.c

t_point	*ft_direction(t_point *p1, t_point *p2);
void	ft_nextpix(int error[2], t_point *delta, t_point *current, t_point *direction);
void	ft_putpixel(t_mlx *mlx, int x, int y, int color);
void	ft_bresenham(t_mlx *fdf, t_point *p1, t_point *p2);

#endif
