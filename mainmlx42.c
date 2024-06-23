/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmlx42.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:09:22 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/23 17:53:39 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MLX_ERROR 1
#define HEIGHT 200
#define WIDTH 200

void	ft_hook(mlx_key_data_t keydata, void* param)
{
	mlx_t* window = (mlx_t*)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(window);
		else
			printf("%d has been pressed\n", keydata.key);
	}
}
int	main()
{
	mlx_t *window;

	if(!(window = mlx_init(WIDTH, HEIGHT, "testone", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_key_hook(window, ft_hook, window);
	mlx_loop(window);
	mlx_terminate(window);
	return (0);
}

//cc mainmlx42.c -IMLX42 -LMLX42/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm
//clang mainmlx42.c -fsanitize=address,undefined -g -IMLX42 -LMLX42/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm -o mainmlx42