/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:05:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/21 11:28:31 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minilibx_macos/mlx.h"
#include "minilibx_linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR 1
#define HEIGHT 200
#define WIDTH 200

int	main ()
{
	void	*mlx_connection;
	void	*mlx_window1;
	void	*mlx_window2;

	mlx_connection = mlx_init();
	if (NULL == mlx_connection)
		return (MALLOC_ERROR);
	mlx_window1 = mlx_new_window(mlx_connection, HEIGHT, WIDTH, "WindowTest 1");
	if (NULL == mlx_window1)
	{
		mlx_destroy_window(mlx_connection, mlx_window1);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	mlx_window1 = mlx_new_window(mlx_connection, HEIGHT, WIDTH, "WindowTest 2");
	if (NULL == mlx_window2)
	{
		mlx_destroy_window(mlx_connection, mlx_window2);
		free(mlx_connection);
		return (MALLOC_ERROR);
	}
	mlx_loop(mlx_connection);
	mlx_destroy_window(mlx_connection, mlx_window1);
	mlx_destroy_window(mlx_connection, mlx_window2);
	free(mlx_connection);
}

//cc main.c -Iminilibx_macos -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
//cc main.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext