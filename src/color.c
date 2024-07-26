/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/26 16:53:48 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_color_shift(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

static int	ft_color_process(int start, int end, double percentage)
{
	return ((int)round((1 - percentage) * start + percentage * end));
}

int	ft_color_gradient(int start_color, int end_color, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = ft_color_process(ft_color_shift(start_color, 16),
			ft_color_shift(end_color, 16), percentage);
	g = ft_color_process(ft_color_shift(start_color, 8),
			ft_color_shift(end_color, 8), percentage);
	b = ft_color_process(ft_color_shift(start_color, 0),
			ft_color_shift(end_color, 0), percentage);
	return ((r << 16) | (g << 8) | b);
}