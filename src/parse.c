/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:48:22 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/22 18:59:50 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_color(char *z)
{
	int		color;

	if (!z)
		return (0);
	if (z[0] == '0' && (z[1] == 'x' || z[1] == 'X'))
		z += 2;
	color = ft_atoi_base(z, 16);
	if (color < 0)
		return (0);
	return (color);
}

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
		p[i].x = i;
		p[i].y = y;
		z = points[i];
		p[i].z = ft_atoi(z);
		if (ft_strchr(z, ','))
			p[i].color = ft_color(ft_strchr(z, ',') + 1);
		else
			p[i].color = DEFAULT_COLOR;
		i++;
	}
	ft_free_split(points);
	return (1);
}

static int	ft_parse_increment(t_map *map, char *line, int *y)
{
	if (!ft_parse_line(line, map->points[*y], *y, map->width))
		return (0);
	(*y)++;
	return(1);
}

t_map	*ft_parse_map(char *map_file)
{
	t_map	*map;
	int		fd;

	map = ft_map_process(map_file);
	fd = open(map_file, O_RDONLY)
	if(!map || fd < 0)
	{
		ft_map_free(map);
		if (fd > 0)
			close(fd);
		return (NULL);
	}
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!ft_parse_increment(map, line, &y))
		{
			free(line);
			close(fd);
			ft_map_free(map);
			return (NULL);
		}
		free(line);
	}
	close(fd);
	return (map);
}
