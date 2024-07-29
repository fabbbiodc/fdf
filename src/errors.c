/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:03:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:20:10 by fdi-cecc         ###   ########.fr       */
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
	if (errorcode == ERR_MAP)
		ft_printf("Error: failed map\n");
	return (1);
}

void	ft_free_split(char **points)
{
	int	i;

	i = 0;
	if (points)
	{
		while (points[i])
		{
			free(points[i]);
			i++;
		}
		free(points);
	}
}

int	ft_free(t_mlx *fdf)
{
	if (!fdf)
		return (EXIT_FAILURE);
	if (fdf->cam)
	{
		free(fdf->cam);
		fdf->cam = NULL;
	}
	if (fdf->map)
	{
		ft_map_free(fdf->map);
		fdf->map = NULL;
	}
	free(fdf);
	return (EXIT_SUCCESS);
}

void	ft_cleanup_mlx(t_mlx *fdf)
{
	if (fdf->img)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
	}
	if (fdf->win)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf->win = NULL;
	}
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
		fdf->mlx = NULL;
	}
}

int	ft_terminate(t_mlx *fdf)
{
	if (!fdf)
		return (EXIT_FAILURE);
	ft_cleanup_mlx(fdf);
	if (fdf->img_att)
	{
		free(fdf->img_att);
		fdf->img_att = NULL;
	}
	ft_free(fdf);
	exit(EXIT_SUCCESS);
}
