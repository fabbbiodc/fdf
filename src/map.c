/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:11:09 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/23 13:20:00 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_map_rows(t_map *map)
{
	int	i;

	i = 0;
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
			return (0);
		}
		i++;
	}
	return (1);
}

static t_map	*ft_map_allocate(int width, int height)
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

static int	ft_map_size(char *map, int *width, int *height)
{
	int		fd;
	char	*line;
 	ft_printf("Entering ft_map_size\n");
	ft_printf("Opening file %s\n", map);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Failed to open file.\n");
		return (0);
	}
	ft_printf("File opened successfully. File descriptor: %d\n", fd);
	*width = 0;
	*height = 0;
	ft_printf("Getting line with get_next_line\n");
	line = get_next_line(fd);
	ft_printf("get_next_line returned. Line: %s\n", line ? line : "NULL");
	while (line)
	{
		ft_printf("Processing line %d\n", *height + 1);
		if (*height == 0)
		{
			*width = ft_word_count(line, ' ');
			ft_printf("Width calculated: %d\n", *width);
		}
		ft_printf("Current height: %d\n", *height);
		free(line);
		ft_printf("About to call get_next_line again\n");
		(*height)++;
		line = get_next_line(fd);
		ft_printf("get_next_line returned. Line: %s\n", line ? line : "NULL");
	}
	close(fd);
	ft_printf("File closed. Final dimensions: width=%d, height=%d\n", *width, *height);
	ft_printf("Exiting ft_map_size\n");
	return (1);
}

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

t_map	*ft_map_process(char *map_file)
{
	t_map	*map;
	int		width;
	int		height;

	ft_printf("Entering ft_map_process\n");
	if (!ft_map_size(map_file, &width, &height))
	{
		ft_printf("failed to get map dimension\n");
		return (NULL);
	}
	ft_printf("Map dimensions: width=%d, height=%d\n", width, height);
	ft_printf("Allocating map structure\n");
	map = ft_map_allocate(width, height);
	if (!map)
	{
		ft_printf("Failed to allocate map\n");
		return (NULL);
	}
	ft_printf("Map allocated successfully\n");
	ft_printf("Exiting ft_map_process\n");
	return (map);
}
