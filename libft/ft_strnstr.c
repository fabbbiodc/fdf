/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:21:56 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/04/26 15:47:31 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!*needle)
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		if (hay[i] == needle[0])
		{
			while (needle[k] && hay[i + k] == needle[k] && i + k < len)
			{
				if (needle[k + 1] == '\0')
					return ((char *)&hay[i]);
				k++;
			}
		}
		i++;
	}
	return (0);
}
