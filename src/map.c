/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:11:09 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:39:56 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_map_rows:
Allocates memory for each row of points in the map.
// Called from:
ft_map_allocate
// Output:
Allocates memory for point arrays within the map structure.*/
int	ft_map_rows(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->points[i] = (t_pnt *)malloc(map->width * sizeof(t_pnt));
		if (!map->points[i])
		{
			while (i > 0)
			{
				i--;
				free(map->points[i]);
			}
			free(map->points);
			return (0);
		}
		i++;
	}
	return (1);
}

/* ft_map_allocate:
Allocates memory for the entire map structure.
// Called from:
ft_map_process
// Output:
Creates and initializes a new map structure with allocated memory for points.*/
t_map	*ft_map_allocate(int width, int height)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->height = height;
	map->width = width;
	map->points = (t_pnt **)malloc(height * sizeof(t_pnt *));
	if (!map->points)
	{
		free(map);
		return (NULL);
	}
	if (!ft_map_rows(map))
	{
		free(map->points);
		free(map);
		return (NULL);
	}
	return (map);
}

/* ft_map_size:
Determines the dimensions of the map from the input file.
// Called from:
ft_map_process
// Output:
Sets the width and height of the map based on file contents.*/
int	ft_map_size(char *map, int *width, int *height)
{
	int		fd;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (0);
	*width = 0;
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*height == 0)
			*width = ft_word_count(line, ' ');
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

/* ft_map_free:
Frees all allocated memory for the map structure.
// Called from:
ft_free, ft_parse_map (in case of error)
// Output:
Deallocates all memory associated with the map structure.*/
void	ft_map_free(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->points)
		{
			i = 0;
			while (i < map->height)
			{
				if (map->points[i])
					free(map->points[i]);
				i++;
			}
			free(map->points);
		}
		free(map);
	}
}

/* ft_map_process:
Processes the input file to create the map structure.
// Called from:
ft_parse_map
// Output:
Creates and returns a fully allocated map structure based on the input file.*/
t_map	*ft_map_process(char *map_file)
{
	t_map	*map;
	int		width;
	int		height;

	if (!ft_map_size(map_file, &width, &height))
		return (NULL);
	map = ft_map_allocate(width, height);
	if (!map)
		return (NULL);
	return (map);
}
