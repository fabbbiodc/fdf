/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:11:09 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/16 12:04:16 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static int	ft_map_rows(t_map *map)
{
	int	i;

	while (i < map->height)
	{
		map->points[i] = (t_point *)malloc(map->width * sizeof(t_point));
		if (!map->points[i])
		{
			while (i > 0)
			{
				i--;
				free(map->points[i]);
			}
			free(map->points);
			return (NULL);
		}
		i++;
	}
	return (1);
}

static t_map	*ft_map_allocate(width, height)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->height = height;
	map->width = width;
	map->points = (t_point **)malloc(height * sizeof(t_point *));
	if (!map->points)
	{
		free(map)
		return (NULL);
	}
	if (!ft_map_rows(map))
	{
		free(map);
		return (NULL);
	}
	return (map);
}

static int	ft_map_size(char *map, int *width, int *height)
{
	int		fd;
	char	*line;

	fd = open(map, 0_RDONLY);
	if (fd < 0)
		return (0);
	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*height == 0)
			*width = ft_words(line, ' ');
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

t_map	ft_map_parse(char *map)
{
	t_map	*map;
	int		width;
	int		height;

	if (!ft_map_size(map, &width, &height))
		return (NULL);
}
