/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:53:58 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/28 17:45:41 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"
#include "line.h"

int ft_keyreact(int key, t_mlx *line)
{
	if (key == 65307)
	{
		printf("ESC has been pressed(%d)\n", key);
		mlx_destroy_image(line->mlx, line->img);
		mlx_destroy_window(line->mlx, line->win);
		free(line->mlx);
		free(line);
		exit (1);
	}
	printf("%d has been pressed\n", key);
	return (0);
}

int	main()
{
	t_mlx	*line;

	line = (t_mlx *)malloc(sizeof (t_mlx));
	line->mlx = mlx_init();
	if(!line->mlx)
	{
		free(line);
	}
	line->win = mlx_new_window(line->mlx, 400, 400, "Window");
	if (!line->win)
	{
		free(line->mlx);
		free(line);
	}
	line->img = mlx_new_image(line->mlx, 400,400);
	if (!line->img)
	{
		mlx_destroy_window(line->mlx, line->win);
		free(line->mlx);
		free(line);
		return (0);
	}
	mlx_key_hook(line->win, ft_keyreact, line);
	mlx_loop(line->mlx);
	mlx_destroy_image(line->mlx, line->img);
	mlx_destroy_window(line->mlx, line->win);
	free(line->mlx);
	free(line);
	return (0);
}
