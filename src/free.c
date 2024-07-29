/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:03:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:25:01 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_free_split:
Frees memory allocated for an array of strings.
// Called from:
ft_parse_line
// Output:
Deallocates memory for each string in the array and for the array itself.*/
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

/* ft_free:
Frees all allocated memory in the main fdf structure.
// Called from:
ft_terminate
// Output:
Deallocates memory for camera and map structures,
then frees the main fdf structure.*/
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

/* ft_cleanup_mlx:
Cleans up MLX-related resources (images, windows, and display).
// Called from:
ft_terminate
// Output:
Destroys MLX images and windows, and frees the MLX pointer.*/
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

/* ft_terminate:
Performs a complete cleanup and exits the program.
// Called from:
ft_keyreact, main (in case of initialization failure)
// Output:
Calls cleanup functions, frees all allocated memory, and exits the program.*/
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
