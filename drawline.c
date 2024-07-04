/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/04 15:51:43 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_draw(t_mlx *fdf)
{
    if (!fdf || !fdf->mlx || !fdf->win || !fdf->img || !fdf->img_att || !fdf->img_att->addr)
    {
        fprintf(stderr, "Error: Invalid MLX data structures\n");
        return (1);
    }

    t_point p1, p2;
    ft_definepoint(&p1, 50, 50);
    ft_definepoint(&p2, 200, 200);
    ft_bresenham(fdf, &p1, &p2);

    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);

    return (0);
}
t_point	*ft_direction(t_point *p1, t_point *p2)
{
	t_point *direction;

	direction = malloc(sizeof(t_point));
	if (!direction)
		return (0);
	if (p1->x < p2->x)
		direction->x = 1;
	if (p1->x > p2->x)
		direction->x = -1;
	if (p1->y < p2->y)
		direction->y = 1;
	if (p1->y > p2->y)
		direction->y = -1;
	return (direction);
}
void	ft_nextpix(int error[2], t_point *delta, t_point *current, t_point *direction)
{
	error[1] = 2 * error[0];
	if (error[1] > delta->y)
	{
		current->x += direction->x;
		error[0] += delta->y;
	}
	if (error[1] < delta->x)
	{
		current->y += direction->y;
		error[0] += delta->x;
	}
}
void ft_putpixel(t_mlx *fdf, int x, int y, int color)
{
    int offset;
	
	offset = y * fdf->img_att->linesize + x * (fdf->img_att->bpp / 8);
    if (offset < 0 || offset >= WIN_WIDTH * WIN_HEIGHT * (fdf->img_att->bpp / 8))
        return ;

    char *pix = fdf->img_att->addr + offset;
    *(unsigned int *)pix = color;
}
void ft_bresenham(t_mlx *fdf, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	*direction;
	t_point current;
	int		error[2];

	current = *p1;
	delta.x = ft_abs(p2->x - p1->x);
	delta.y = -ft_abs(p2->y - p1->y);
	direction = ft_direction(p1, p2);
	error[0] = delta.x + delta.y;
	if (!direction)
		return ;
	while (current.x != p2->x || current.y != p2->y)
	{
		//mlx_pixel_put(fdf->mlx, fdf->win, current.x, current.y, COLOR);
		ft_putpixel(fdf, current.x, current.y, COLOR);
		ft_nextpix(error, &delta, &current, direction);
	}
}
