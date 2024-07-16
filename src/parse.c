/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:48:22 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/16 20:08:14 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"fdf.h"

int	ft_parse_line(char *line, t_point *p, int y, int width)
{
	char	**points;
	char	*z;
	int		i;

	points = ft_split(line, ' ');
	if (!points)
		return (0);
	i = 0;
	while (i < width)
	{
		p[i]->x = i;
		p[i]->y = y;
		z = points[i];
		p[i]->z = ft_atoi(z);
	}
}

t_map	ft_parse_map(char *map)
{
	t_map	*map;
	int		width;
	int		height;

	if (!ft_map_size(map, &width, &height))
		return (NULL);
}