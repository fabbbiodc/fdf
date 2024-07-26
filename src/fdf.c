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
		ft_terminate(fdf);
	else if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT || key == KEY_PLU || key == KEY_MIN
		|| key == KEY_A || key == KEY_D || key == KEY_P || key == KEY_O || key == KEY_L)
	{
		ft_cam_control(key, fdf);
		ft_init_image(fdf);
		ft_draw(fdf);
	}
	return (0);
}

static t_mlx	*ft_fdf_allocate(void)
{
	t_mlx	*fdf;

	fdf = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!fdf)
		ft_printf("Memory allocation for fdf failed\n");
	return (fdf);
}

static int	ft_argcheck(int argc)
{
	if (argc != 2)
	{
		ft_printf("Try like this: ./fdf <map file>\n");
		return (0);
	}
	return (1);
}

static void	ft_set_hooks(t_mlx *fdf)
{
	mlx_key_hook(fdf->win, ft_keyreact, fdf);
	mlx_expose_hook(fdf->win, ft_draw, fdf);
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	if (!ft_argcheck(argc))
		return (1);
	fdf = ft_fdf_allocate();
	if (!fdf || !ft_fdf_init(fdf, argv[1]))
	{
		ft_terminate(fdf);
		return (1);
	}
	ft_draw(fdf);
	ft_set_hooks(fdf);
	mlx_loop(fdf->mlx);
	ft_terminate(fdf);
	return (0);
}