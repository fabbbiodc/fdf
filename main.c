/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:05:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/20 17:52:43 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR 1
#define HEIGHT 200
#define WIDTH 200

int	main ()
{
	void *mlx_connection;
	void *mlx_window;

	mlx_connection = mlx_init();
	if (NULL == mlx_connection)
		return (MALLOC_ERROR);
	mlx_window = mlx_new_window(mlx_connection, HEIGHT, WIDTH, "WindowTest");
	if (NULL == mlx_window)
	{
		mlx_destroy_window(mlx_connection, mlx_window);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	mlx_loop(mlx_connection);
	mlx_destroy_window(mlx_connection, mlx_window);
	free(mlx_connection);
}

//cc main.c -Iminilibx_macos -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit