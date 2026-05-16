/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:48:55 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 18:48:05 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stash(char *buffer, char **stash)
{
	char	*temp;

	if (!*stash)
		return (ft_strdup(buffer));
	temp = ft_strjoin(*stash, buffer);
	free(*stash);
	if (temp == NULL)
		return (NULL);
	*stash = temp;
	return (*stash);
}

static char	*ft_line(char **stash)
{
	char	*temp;
	char	*line;
	char	*newline_ptr;

	if (!*stash)
		return (NULL);
	newline_ptr = ft_strchr(*stash, '\n');
	if (newline_ptr)
	{
		*newline_ptr = '\0';
		line = ft_strjoin(*stash, "\n");
		temp = ft_strdup(newline_ptr + 1);
		free(*stash);
		*stash = temp;
		return (line);
	}
	return (NULL);
}

static int	ft_read(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	*stash = ft_stash(buffer, stash);
	free(buffer);
	return (bytes_read);
}

static char	*ft_remain(char **stash)
{
	char	*line;

	if (*stash && **stash)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	else
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		line = ft_line(&stash[fd]);
		if (line)
			return (line);
		bytes_read = ft_read(fd, &stash[fd]);
		if (bytes_read < 0)
		{
			free(stash[fd]);
			stash[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			return (ft_remain(&stash[fd]));
	}
}
