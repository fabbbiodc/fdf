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

int	ft_keyreact(int key, t_mlx *fdf)
{
	if (key == KEY_ESC)
	{
		ft_terminate(fdf);
		exit(0);
	}
	else if (key == KEY_UP)
	{
		fdf->cam->alpha += ROTATION;
		ft_init_image(fdf);
		ft_draw(fdf);
	}
	else if (key == KEY_DOWN)
	{
		fdf->cam->alpha -= ROTATION;
		ft_init_image(fdf);
		ft_draw(fdf);
	}
	return (0);
}

static int ft_create_image(t_mlx *fdf)
{
    fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!fdf->img)
        return (0);
    fdf->img_att = (t_img *)malloc(sizeof(t_img));
    if (!fdf->img_att)
    {
        mlx_destroy_image(fdf->mlx, fdf->img);
        fdf->img = NULL;
        return (0);
    }
    return (1);
}

int	ft_init_image(t_mlx *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->img_att)
		free(fdf->img_att);
	fdf->img = NULL;
	fdf->img_att = NULL;
	if (!ft_create_image(fdf))
		return (0);
	fdf->img_att->addr = mlx_get_data_addr(fdf->img, &fdf->img_att->bpp,
		&fdf->img_att->linesize, &fdf->img_att->endian);
	if (!fdf->img_att->addr)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		free(fdf->img_att);
		fdf->img = NULL;
		fdf->img_att = NULL;
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;
	ft_printf("Program started\n");

	if (argc != 2)
	{
		ft_printf("try like this: ./fdf <map file>\n");
		return (1);
	}
	void *test = malloc(10);
	if (!test)
	{
		ft_printf("Test allocation failed\n");
		return (ft_error_handle(ERR_MALLOC));
	}
	ft_printf("Test allocation succeeded\n");
	free(test);
	ft_printf("Map file: %s\n", argv[1]);
	printf("Size of t_mlx: %zu bytes\n", sizeof(t_mlx));
	ft_printf("Allocating fdf structure\n");
	fdf = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!fdf)
	{
		ft_printf("memory allocation failed\n");
		return (ft_error_handle(ERR_MALLOC));
	}
	ft_printf("Malloc Allocated\n");
	ft_printf("About to parse map\n");
	fdf->map = ft_parse_map(argv[1]);
	ft_printf("Map parsed\n");
	if (!fdf->map)
	{
		ft_printf("Map parse failed\n");
		return (ft_error_handle(ERR_MAP), ft_terminate(fdf));
	}
	ft_printf("Map parse success\n");
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		ft_printf("MLX initialization failed\n");
		return (ft_error_handle(ERR_INIT));
	}
	ft_printf("MLX initialization success\n");
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Window");
	if (!fdf->win)
	{
		ft_printf("MLX window failed\n");
		return (ft_error_handle(ERR_WIN), ft_terminate(fdf), 1);
	}
	ft_printf("MLX window success\n");
	if (!ft_init_image(fdf))
		return (ft_error_handle(ERR_IMG), ft_terminate(fdf), 1);
	if (ft_cam_init(fdf) != EXIT_SUCCESS)
		return (ft_error_handle(ERR_CAM));
	ft_cam_params(fdf);
	ft_draw(fdf);
	mlx_key_hook(fdf->win, ft_keyreact, fdf);
	mlx_expose_hook(fdf->win, ft_draw, fdf);
	ft_printf("Hooks set up successfully\n");
	ft_printf("Starting MLX loop\n");
	mlx_loop(fdf->mlx);
	ft_printf("MLX loop ended\n");
	ft_terminate(fdf);
	return (0);
}
