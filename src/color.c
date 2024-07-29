/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 17:02:03 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_color_shift(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

int	ft_color_process(int start, int end, double percentage)
{
	return ((int)round((1 - percentage) * start + percentage * end));
}

int	ft_fade_color(int color, double depth, double max_depth)
{
	double	fade_factor;
	int		r;
	int		g;
	int		b;

	fade_factor = pow((max_depth - depth) / max_depth, 2.5);
	fade_factor = fmin(fmax(fade_factor, 0.1), 2.0);
	r = ((color >> 16) & 0xFF) * fade_factor;
	g = ((color >> 8) & 0xFF) * fade_factor;
	b = (color & 0xFF) * fade_factor;
	return ((r << 16) | (g << 8) | b);
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

void	ft_toggle_color(t_mlx *fdf)
{
	fdf->cam->color_scheme++;
	if (fdf->cam->color_scheme >= COLOR_SCHEME_COUNT)
		fdf->cam->color_scheme = 0;
}
