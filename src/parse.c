/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:48:22 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:39:52 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_color:
Extracts the color value from a string, handling hexadecimal format.
// Called from:
ft_set_point
// Output:
Returns the parsed color value as an integer.*/
int	ft_color(char *z)
{
	int	color;

	if (!z)
		return (0);
	if (z[0] == '0' && (z[1] == 'x' || z[1] == 'X'))
		z += 2;
	color = ft_atoi_base(z, 16);
	if (color < 0)
		return (0);
	return (color);
}

/* ft_set_point:
Initializes a point structure with coordinates and color.
// Called from:
ft_parse_line
// Output:
Populates a point structure with x, y, z coordinates and color.*/
void	ft_set_point(t_pnt *p, int i, int y, char *z)
{
	p->x = i;
	p->y = y;
	p->depth = 0;
	p->z = ft_atoi(z);
	if (ft_strchr(z, ','))
		p->color = ft_color(ft_strchr(z, ',') + 1);
	else
		p->color = DEFAULT_COLOR;
}

/* ft_parse_line:
Parses a single line of the map file, setting up points.
// Called from:
ft_parse_loop
// Output:
Populates an array of points based on the parsed line data.*/
int	ft_parse_line(char *line, t_pnt *p, int y, int width)
{
	char	**points;
	int		i;

	points = ft_split(line, ' ');
	if (!points)
		return (0);
	i = 0;
	while (i < width)
	{
		ft_set_point(&p[i], i, y, points[i]);
		i++;
	}
	ft_free_split(points);
	return (1);
}

/* ft_parse_loop:
Iterates through all lines of the map file, parsing each one.
// Called from:
ft_parse_map
// Output:
Fills the entire map structure with parsed point data.*/
int	ft_parse_loop(t_map *map, int fd)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!ft_parse_line(line, map->points[y], y, map->width))
		{
			free(line);
			return (0);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	return (1);
}

/* ft_parse_map:
Orchestrates the entire map parsing process from file to structure.
// Called from:
ft_fdf_init
// Output:
Returns a fully populated map structure based on the input file.*/
t_map	*ft_parse_map(char *map_file)
{
	t_map	*map;
	int		fd;

	map = ft_map_process(map_file);
	fd = open(map_file, O_RDONLY);
	if (!map || fd < 0)
	{
		ft_map_free(map);
		if (fd >= 0)
			close(fd);
		return (NULL);
	}
	if (!ft_parse_loop(map, fd))
	{
		ft_map_free(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
