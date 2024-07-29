/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:57 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:13:04 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_color_shift:
Extracts a specific color component (red, green, or blue) from a color value.
// Called from:
ft_color_gradient
// Output:
Returns the extracted color component as an integer.*/
int	ft_color_shift(int color, int shift)
{
	return ((color >> shift) & 0xFF);
}

/* ft_color_process:
Calculates an intermediate color value between two colors based on a percentage.
// Called from:
ft_color_gradient
// Output:
Returns the calculated intermediate color value.*/
int	ft_color_process(int start, int end, double percentage)
{
	return ((int)round((1 - percentage) * start + percentage * end));
}

/* ft_fade_color:
Applies a depth-based fading effect to a color.
// Called from:
ft_dda_loop
// Output:
Returns the faded color value.*/
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

/* ft_color_gradient:
Calculates a color gradient between two colors based on a percentage.
// Called from:
ft_dda_loop
// Output:
Returns the calculated gradient color.*/
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

/* ft_toggle_color:
Cycles through different color schemes for the map.
// Called from:
ft_cam_control
// Output:
Updates the color scheme in the fdf structure.*/
void	ft_toggle_color(t_mlx *fdf)
{
	fdf->cam->color_scheme++;
	if (fdf->cam->color_scheme >= COLOR_SCHEME_COUNT)
		fdf->cam->color_scheme = 0;
}
