/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:20:32 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_draw_points:
Draws connections between adjacent points in the map.
// Called from:
ft_draw
// Output:
Renders lines between adjacent points on the screen.*/
void	ft_draw_points(t_mlx *fdf, int y, int x)
{
	t_pnt	p1;
	t_pnt	p2;

	p1 = fdf->map->points[y][x];
	ft_render(&p1, fdf);
	p1.color = ft_get_color(fdf, &p1);
	if (x < (fdf->map->width - 1))
	{
		p2 = fdf->map->points[y][x + 1];
		ft_render(&p2, fdf);
		p2.color = ft_get_color(fdf, &p2);
		ft_dda(fdf, &p1, &p2);
	}
	if (y < (fdf->map->height - 1))
	{
		p2 = fdf->map->points[y + 1][x];
		ft_render(&p2, fdf);
		p2.color = ft_get_color(fdf, &p2);
		ft_dda(fdf, &p1, &p2);
	}
}

/* ft_get_color:
Determines the color for a point based on its height
and the current color scheme.
// Called from:
ft_draw_points
// Output:
Returns the color value for the given point.*/
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

/* ft_draw:
Renders the entire map by iterating through all points and drawing connections.
// Called from:
ft_set_hooks (as part of mlx_expose_hook), ft_update
// Output:
Renders the complete map on the screen and updates the window.*/
int	ft_draw(t_mlx *fdf)
{
	int	x;
	int	y;

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
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_panel_draw(fdf);
	return (0);
}

/* ft_putpixel:
Places a single pixel on the screen at the specified coordinates
with the given color.
Performs bit shifting operations to correctly place the color value in memory,
accounting for the pixel format.
// Called from:
ft_dda_loop
// Output:
Modifies the image data to set a pixel color, using pointer arithmetic and
bit operations to efficiently write to the correct memory location.*/
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
