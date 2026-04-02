/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/30 09:26:32 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_color(t_mlx *fdf, t_pnt *point)
{
	int	colors[COLOR_SCHEME_COUNT];

	if (point && point->color != DEFAULT_COLOR)
		return (point->color);
	colors[0] = COLOR_DEFAULT;
	colors[1] = COLOR_RED;
	colors[2] = COLOR_GREEN;
	colors[3] = COLOR_BLUE;
	colors[4] = COLOR_YELLOW;
	colors[5] = COLOR_MAGENTA;
	colors[6] = COLOR_CYAN;
	colors[7] = COLOR_PURPLE;
	return (colors[fdf->cam->color_scheme]);
}

static void	ft_draw_line(t_mlx *fdf, t_pnt *p1, t_pnt *p2)
{
	t_pnt	delta;
	t_pnt	step;
	t_pnt	current;
	int		steps;
	double	progress;
	int		x;
	int		y;
	int		color;

	if (isinf(p1->x) || isinf(p1->y) || isinf(p2->x) || isinf(p2->y))
		return ;
	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	steps = (int)fmax(fabs(delta.x), fabs(delta.y));
	if (steps == 0)
		return ;
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	current = *p1;
	progress = 0;
	while (progress <= 1)
	{
		x = (int)round(current.x);
		y = (int)round(current.y);
		if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		{
			color = ft_color_gradient(p1->color, p2->color, progress);
			if (fdf->cam->proj == PROJ_1PT || fdf->cam->proj == PROJ_2PTS)
				color = ft_fade_color(color, p1->depth + (p2->depth - p1->depth)
						* progress, fdf->cam->min_depth, fdf->cam->max_depth);
			ft_putpixel(fdf, x, y, color);
		}
		current.x += step.x;
		current.y += step.y;
		progress += 1.0 / steps;
		if (fabs(current.x - p1->x) > fabs(delta.x)
			|| fabs(current.y - p1->y) > fabs(delta.y))
			progress = 2;
	}
}

void	ft_render_cached(t_mlx *fdf)
{
	t_matrix	rot;
	t_pnt		temp;
	int			x;
	int			y;
	int			c1;

	rot = ft_matr_final(fdf);
	fdf->cam->min_depth = INFINITY;
	fdf->cam->max_depth = -INFINITY;
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			temp = fdf->map->points[y][x];
			ft_apply_transformations(&temp, fdf, rot);
			ft_apply_projection_cached(&temp, fdf);
			fdf->screen[y][x] = temp;
			c1 = ft_get_color(fdf, fdf->map->points[y] + x);
			fdf->screen[y][x].color = c1;
			if (!isinf(temp.x) && !isinf(temp.y))
			{
				fdf->cam->min_depth = fmin(fdf->cam->min_depth, temp.depth);
				fdf->cam->max_depth = fmax(fdf->cam->max_depth, temp.depth);
			}
			x++;
		}
		y++;
	}
}

int	ft_draw(t_mlx *fdf)
{
	int	x;
	int	y;

	ft_render_cached(fdf);
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < (fdf->map->width - 1))
				ft_draw_line(fdf, &fdf->screen[y][x], &fdf->screen[y][x + 1]);
			if (y < (fdf->map->height - 1))
				ft_draw_line(fdf, &fdf->screen[y][x], &fdf->screen[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_panel_draw(fdf);
	return (0);
}

void	ft_putpixel(t_mlx *fdf, int x, int y, int color)
{
	int		offset;
	char	*pix;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = y * fdf->img_att->linesize + x * (fdf->img_att->bpp / 8);
	pix = fdf->img_att->addr + offset;
	*(unsigned int *)pix = color;
}
