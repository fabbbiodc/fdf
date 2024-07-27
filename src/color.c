/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/27 15:37:42 by fdi-cecc         ###   ########.fr       */
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

int ft_fade_color(int color, double depth, double max_depth)
{
    // Increase the power for more intense fading
    double fade_factor = pow((max_depth - depth) / max_depth, 2.5);
    
    // Adjust the range to make the fading more pronounced
    fade_factor = fmin(fmax(fade_factor, 0.1), 2.0); // Lowered minimum to 0.1 for more intensity

    int r = ((color >> 16) & 0xFF) * fade_factor;
    int g = ((color >> 8) & 0xFF) * fade_factor;
    int b = (color & 0xFF) * fade_factor;
    
    return (r << 16) | (g << 8) | b;
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
