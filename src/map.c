/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:11:09 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/15 17:37:25 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/fdf.h"

static t_map	ft_map_allocate(width, height)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	map->height = height;
	map->width = width;
	map->points = (t_points **)malloc(sizeof(t_point *))
	if

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