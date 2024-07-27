/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/27 15:17:32 by fdi-cecc         ###   ########.fr       */
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


void    ft_putpixel(t_mlx *fdf, int x, int y, int color)
{
    int     offset;
    char    *pix;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return ;
    offset = y * fdf->img_att->linesize + x * (fdf->img_att->bpp / 8);
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

static int ft_is_offscreen(double x, double y)
{
    return (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT);
}

void ft_dda(t_mlx *fdf, t_point *p1, t_point *p2)
{
    t_point delta;
    t_point step;
    t_point current;
    int     steps;
    double  progress;

    if (isinf(p1->x) || isinf(p1->y) || isinf(p2->x) || isinf(p2->y))
        return; // Don't render lines with infinite points

    if (ft_is_offscreen(p1->x, p1->y) && ft_is_offscreen(p2->x, p2->y))
        return;

    delta.x = p2->x - p1->x;
    delta.y = p2->y - p1->y;
    steps = (int)fmax(fabs(delta.x), fabs(delta.y));

    if (steps == 0)
        return;

    step.x = delta.x / steps;
    step.y = delta.y / steps;
    current = *p1;
    progress = 0;

    while (progress <= 1)
    {
        if (!ft_is_offscreen(current.x, current.y))
        {
            current.color = ft_color_gradient(p1->color, p2->color, progress);
            ft_putpixel(fdf, (int)round(current.x), (int)round(current.y), current.color);
        }
        current.x += step.x;
        current.y += step.y;
        progress += 1.0 / steps;

        // Break if we've gone too far
        if (fabs(current.x - p1->x) > fabs(delta.x) || fabs(current.y - p1->y) > fabs(delta.y))
            break;
    }
}