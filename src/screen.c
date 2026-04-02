/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:00:00 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/30 11:00:00 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_alloc_screen(t_mlx *fdf)
{
	int	i;

	fdf->screen = (t_pnt **)malloc(fdf->map->height * sizeof(t_pnt *));
	if (!fdf->screen)
		return ;
	i = 0;
	while (i < fdf->map->height)
	{
		fdf->screen[i] = (t_pnt *)malloc(fdf->map->width * sizeof(t_pnt));
		if (!fdf->screen[i])
		{
			while (i > 0)
			{
				i--;
				free(fdf->screen[i]);
			}
			free(fdf->screen);
			fdf->screen = NULL;
			return ;
		}
		i++;
	}
}

void	ft_free_screen(t_mlx *fdf)
{
	int	i;

	if (fdf->screen)
	{
		i = 0;
		while (i < fdf->map->height)
		{
			if (fdf->screen[i])
			{
				free(fdf->screen[i]);
				fdf->screen[i] = NULL;
			}
			i++;
		}
		free(fdf->screen);
		fdf->screen = NULL;
	}
}
