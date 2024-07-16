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
		ft_draw(fdf);
	}
	else if (key == KEY_DOWN)
	{
		fdf->cam->alpha -= ROTATION;
		ft_draw(fdf);
	}
	return (0);
}

void	ft_definepoint(t_point *point, double x, double y, double z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

int	ft_init_image(t_mlx *fdf)
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
	fdf->img_att->addr = mlx_get_data_addr(fdf->img, &fdf->img_att->bpp,
			&fdf->img_att->linesize, &fdf->img_att->endian);
	if (!fdf->img_att->addr)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		free(fdf->img_att);
		return (0);
	}
	return (1);
}

int	main(void)
{
	t_mlx	*fdf;

	fdf = (t_mlx *)malloc(sizeof(t_mlx));
	if (!fdf)
		return (ft_error_handle(ERR_MALLOC));
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (ft_error_handle(ERR_INIT));
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Window");
	if (!fdf->win)
		return (ft_error_handle(ERR_WIN), ft_terminate(fdf), 1);
	if (!ft_init_image(fdf))
		return (ft_error_handle(ERR_IMG), ft_terminate(fdf), 1);
	if (ft_cam_init(fdf) != EXIT_SUCCESS)
		return (ft_error_handle(ERR_CAM));
	ft_cam_params(fdf);
	if (ft_draw(fdf) != 0)
		return (ft_error_handle(ERR_DRAW), ft_terminate(fdf), 1);
	mlx_key_hook(fdf->win, ft_keyreact, fdf);
	mlx_expose_hook(fdf->win, ft_draw, fdf);
	mlx_loop(fdf->mlx);
	ft_terminate(fdf);
	return (0);
}