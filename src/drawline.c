/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/25 11:57:31 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_points(t_mlx *fdf, int y, int x)
{
	t_point	p1;
	t_point	p2;

	p1 = fdf->map->points[y][x];
	ft_render(&p1, fdf);
	if (x < (fdf->map->width -1))
	{
		p2 = fdf->map->points[y][x + 1];
		ft_render(&p2, fdf);
		ft_dda(fdf, &p1, &p2);
	}
	if (y < (fdf->map->height - 1))
	{
		p2 = fdf->map->points[y + 1][x];
		ft_render(&p2, fdf);
		ft_dda(fdf, &p1, &p2);
	}
}

int	ft_draw(t_mlx *fdf)
{
	int		x;
	int		y;

	ft_printf("Starting ft_draw\n");
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			ft_draw_points(fdf, y, x);
			x++;
		}
		y++;
	}
	ft_printf("Finished ft_draw\n");
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}


void	ft_putpixel(t_mlx *fdf, int x, int y, int color)
{
	int		offset;
	char	*pix;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
	{
		ft_printf("Pixel out of bounds: (%d, %d)\n", x, y);
		return ;
	}
	offset = y * fdf->img_att->linesize + x * (fdf->img_att->bpp / 8);
	if (offset < 0 || offset >= WIN_WIDTH * WIN_HEIGHT
		* (fdf->img_att->bpp / 8))
	{
		ft_printf("Invalid offset: %d\n", offset);
		return ;
	}
	pix = fdf->img_att->addr + offset;
	*(unsigned int *)pix = color;
}

void	ft_pixel_increment(t_mlx *fdf, t_point *current)
{
    int x = (int)round(current->x);
    int y = (int)round(current->y);
    
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
        ft_putpixel(fdf, x, y, current->color);
}

void	ft_dda(t_mlx *fdf, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	step;
	t_point	current;
	int		steps;
	int		i;

	current = *p1;
	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	steps = fmax(fabs(delta.x), fabs(delta.y));
	if (steps == 0)
		return ;
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	i = -1;
	while (++i <= steps)
	{
		current.color = ft_color_gradient(p1->color, p2->color, ((double)i/steps));
		ft_pixel_increment(fdf, &current);
		current.x += step.x;
		current.y += step.y;
	}
}

