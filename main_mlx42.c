/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx42.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:05:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/23 16:52:59 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MLX_ERROR 1
#define HEIGHT 200
#define WIDTH 200

typedef struct	s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx_data;


int	hook_react(int keysim, t_mlx_data *data)
{
	if (keysim == MLX_KEY_ESCAPE)
	{
		printf("The %d (ESC) has been pressed\n\n", keysim);
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit (1);
	}
	printf("The %d has been pressed\n\n", keysim);
	return (0);
}

int	main ()
{
	t_mlx_data data;

	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "ciaociao", true);
	if (NULL == data.mlx_ptr)
		return (MLX_ERROR);
	// data.win_ptr = mlx_new_window(data.mlx_ptr, HEIGHT, WIDTH, "WindowTest 1");
	// if (NULL == data.win_ptr)
	// {
	// 	mlx_clear_window(data.mlx_ptr, data.win_ptr);
	// 	free(data.mlx_ptr);
	// 	return (MLX_ERROR);
	// }
	mlx_key_hook(data.win_ptr, hook_react, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

//cc main.c -Iminilibx_macos -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit
//cc main.c -Iminilibx_linux -Lminilibx_linux -lmlx -lX11 -lXext
//gcc main.c -IMLX42 -L/MLX42/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm 
//clang mainmlx42.c -fsanitize=address,undefined -g -IMLX42 -LMLX42/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm -o mainmlx42