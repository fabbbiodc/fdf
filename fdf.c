/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:53:58 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/03 15:40:55 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"
//#include "minilibx_macos/mlx.h"
#include "fdf.h"

int ft_keyreact(int key, t_mlx *fdf)
{
	if (key == KEY_ESC)
	{
		printf("ESC has been pressed(%d)\n", key);
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(fdf->mlx);
		exit (1);
	}
	printf("%d has been pressed\n", key);
	return (0);
}

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
void ft_definepoint(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}
int	ft_draw(t_mlx *fdf)
{
	t_point p1;
	t_point	p2;

	mlx_clear_window(fdf->mlx, fdf->win);
	ft_definepoint(&p1, 50, 50);
	ft_definepoint(&p2, 200, 200);
	ft_bresenham(fdf, &p1, &p2);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}
int	main()
{
	t_point	p1;
	t_point p2;

    t_mlx *fdf = (t_mlx *)malloc(sizeof(t_mlx));
    if (!fdf)
    {
        fprintf(stderr, "Error: Failed to allocate memory for fdf\n");
        return (0);
    }
	
	ft_definepoint(&p1, 2, 2);
	ft_definepoint(&p2, 5, 6);
	fdf->mlx = mlx_init();
	if(!fdf->mlx)
	{
		return (0);
	}
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Window");
	if (!fdf->win)
	{
		free(fdf->mlx);
	}
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(fdf->mlx);
		return (0);
	}
	fdf->img_att = (t_img *)malloc(sizeof(t_img));
	if (!fdf->img_att)
	{
		fprintf(stderr, "Error: Failed to allocate memory for image attributes\n");
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(fdf->mlx);
		return (0);
	}
	fdf->img_att->addr = mlx_get_data_addr(fdf->img, &fdf->img_att->bpp, &fdf->img_att->linesize, &fdf->img_att->endian);
	if (!fdf->img_att->addr)
	{
		fprintf(stderr, "Error: Failed to get image data address\n");
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free(fdf->img_att);
		free(fdf->mlx);
		return (0);
	}
	mlx_key_hook(fdf->win, ft_keyreact, fdf);
	mlx_loop_hook(fdf->mlx, &ft_draw, fdf);
	mlx_loop(fdf->mlx);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->mlx);
	return (0);
}
//cc fdf.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext
//cc fdf.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext -fsanitize=address -g -o fdf