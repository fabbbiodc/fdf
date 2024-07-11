/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:28:24 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/11 16:16:45 by fdi-cecc         ###   ########.fr       */
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
	printf("Clearing image buffer\n");
	ft_memset(fdf->img_att->addr, 0, WIN_WIDTH * WIN_HEIGHT * (fdf->img_att->bpp / 8));

    t_point p1, p2, p3, p4, p5;
    ft_definepoint(&p1, -100, -100, 0);
    ft_definepoint(&p2, 100, -100, 0);
    ft_definepoint(&p3, -100, 100, 0);
    ft_definepoint(&p4, 100, 100, 0);
    ft_definepoint(&p5, 0, 0, 100);
	printf("Rendering points\n");
	ft_render(&p1, fdf);
	ft_render(&p2, fdf);
	ft_render(&p3, fdf);
	ft_render(&p4, fdf);
	ft_render(&p5, fdf);
	printf("Drawing lines\n");
    printf("Drawing line 1: p1 to p2\n");
    ft_dda(fdf, &p1, &p2);
    printf("Drawing line 2: p1 to p3\n");
    ft_dda(fdf, &p1, &p3);
    printf("Drawing line 3: p1 to p5\n");
    ft_dda(fdf, &p1, &p5);
    printf("Drawing line 4: p2 to p4\n");
    ft_dda(fdf, &p2, &p4);
    printf("Drawing line 5: p2 to p5\n");
    ft_dda(fdf, &p2, &p5);
    printf("Drawing line 6: p3 to p4\n");
    ft_dda(fdf, &p3, &p4);
    printf("Drawing line 7: p3 to p5\n");
    ft_dda(fdf, &p3, &p5);
    printf("Drawing line 8: p4 to p5\n");
    ft_dda(fdf, &p4, &p5);
	printf("Putting image to window\n");
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);

    return (0);
}
t_point	*ft_direction(t_point *p1, t_point *p2)
{
	t_point *direction;

	direction = malloc(sizeof(t_point));
	if (!direction)
		return (0);
 	direction->x = 0;  // Initialize to 0
    direction->y = 0;  // Initialize to 0
    if (p1->x < p2->x)
        direction->x = 1;
    else if (p1->x > p2->x)
        direction->x = -1;
    if (p1->y < p2->y)
        direction->y = 1;
    else if (p1->y > p2->y)
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
    
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
    {
        printf("Pixel out of bounds: (%d, %d)\n", x, y);
        return;
    }

    offset = y * fdf->img_att->linesize + x * (fdf->img_att->bpp / 8);
    if (offset < 0 || offset >= WIN_WIDTH * WIN_HEIGHT * (fdf->img_att->bpp / 8))
    {
        printf("Invalid offset: %d\n", offset);
        return;
    }

    char *pix = fdf->img_att->addr + offset;
    *(unsigned int *)pix = color;
}

void	ft_dda(t_mlx *fdf, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	step;
	t_point	current;
	double	max_steps;
	int		i;

	current = *p1;
	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	max_steps = fmax(fabs(delta.x), fabs(delta.y));
	if (max_steps == 0)
		return ;
	step.x = delta.x / max_steps;
	step.y = delta.y / max_steps;
	i = -1;
	while (++i <= (int)max_steps && !(current.x < 0 && current.y < 0)
		&& !(current.x >= WIN_WIDTH && current.y >= WIN_HEIGHT))
	{
		if (current.x >= 0 && current.x < WIN_WIDTH
			&& current.y >= 0 && current.y < WIN_HEIGHT)
			ft_putpixel(fdf, (int)round(current.x), (int)round(current.y), COLOR);
		current.x += step.x;
		current.y += step.y;
	}
}
