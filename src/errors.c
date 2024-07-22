/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:03:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/22 15:20:01 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_error_handle(int errorcode)
{
	if (errorcode == ERR_CAM)
		ft_printf("Error: failed camera\n");
	if (errorcode == ERR_STRUCT)
		ft_printf("Error: invalid mlx data structure\n");
	if (errorcode == ERR_MALLOC)
		ft_printf("Error: failed malloc\n");
	if (errorcode == ERR_INIT)
		ft_printf("Error: faile init\n");
	if (errorcode == ERR_WIN)
		ft_printf("Error: failed window\n");
	if (errorcode == ERR_DRAW)
		ft_printf("Error: failed draw\n");
	return (1);
}

int	ft_free(t_mlx *fdf)
{
	if (fdf->cam)
		free(fdf->cam);
	if (fdf->img)
		free(fdf->img_att);
	free (fdf->mlx);
	free (fdf);
	return (EXIT_SUCCESS);
}

int	ft_terminate(t_mlx *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	ft_free(fdf);
	exit(EXIT_SUCCESS);
}
