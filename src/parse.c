/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:48:22 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/23 13:01:57 by fdi-cecc         ###   ########.fr       */
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
static int	ft_parse_loop(t_map *map, int fd)
{
	char	*line;
	int		y;
	int		rslt;

	y = 0;
	rslt = 1;
	line = get_next_line(fd);
	while (line != NULL && rslt)
	{
		rslt = ft_parse_increment(map, line, &y);
		free(line);
		if (rslt)
			line = get_next_line(fd);
	}
	return (rslt);
}

t_map	*ft_parse_map(char *map_file)
{
	t_map	*map;
	int		fd;

	ft_printf("starting to ft_parse_map\n");
	ft_printf("about to run ft_map_process on %s\n", map_file);
	map = ft_map_process(map_file);
	ft_printf("map processed\n");
	ft_printf("opening file\n");
	fd = open(map_file, O_RDONLY);
	if(!map || fd < 0)
	{
		ft_printf("Error: map processing failed or file couldn't be opened\n");
		ft_map_free(map);
		if (fd >= 0)
			close(fd);
		return (NULL);
	}
	ft_printf("file opened successfully\n");
	ft_printf("Starting parse loop\n");
	if (!ft_parse_loop(map, fd))
	{
		ft_printf("Parse loop failed\n");
		ft_map_free(map);
		close(fd);
		return (NULL);
	}
	ft_printf("Parse loop completed successfully\n");
	close(fd);
	ft_printf("file closed\n");
	ft_printf("exiting ft_parse_map\n");
	return (map);
}
