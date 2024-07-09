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
	if (key == KEY_UP || key == KEY_DOWN)
	{
		ft_cam_rotate(key, fdf);
		ft_img_refresh(fdf);
	}
	printf("%d has been pressed\n", key);
	return (0);
}

void ft_definepoint(t_point *point, int x, int y, int z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

int ft_init_image(t_mlx *fdf)
{
    fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!fdf->img)
        return (0);

    fdf->img_att = (t_img *)malloc(sizeof(t_img));
    if (!fdf->img_att)
    {
        mlx_destroy_image(fdf->mlx, fdf->img);
        return (0);
    }
    fdf->img_att->addr = mlx_get_data_addr(fdf->img, &fdf->img_att->bpp, &fdf->img_att->linesize, &fdf->img_att->endian);
    if (!fdf->img_att->addr)
    {
        mlx_destroy_image(fdf->mlx, fdf->img);
        free(fdf->img_att);
        return (0);
    }

    return (1);
}
int main()
{
    t_mlx *fdf = (t_mlx *)malloc(sizeof(t_mlx));
    if (!fdf)
		ft_error_handle(ERR_MALLOC);
    fdf->mlx = mlx_init();
    if (!fdf->mlx)
		ft_error_handle(ERR_INIT);
    fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Window");
    if (!fdf->win)
		(ft_error_handle(ERR_WIN), ft_terminate(fdf));
    if (!ft_init_image(fdf))
		(ft_error_handle(ERR_IMG), ft_terminate(fdf));
	ft_cam_init(fdf);
	ft_cam_params(fdf);
    if (ft_draw(fdf) != 0)
		(ft_error_handle(ERR_DRAW), ft_terminate(fdf));
    mlx_key_hook(fdf->win, ft_keyreact, fdf);
    mlx_loop(fdf->mlx);
    return (0);
}
//cc fdf.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext
//cc fdf.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext -fsanitize=address -g -o fdf
//cc fdf.c drawline.c errors.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext -fsanitize=address -g -o fdf