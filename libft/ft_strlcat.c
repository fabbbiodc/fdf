/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:32:26 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/04/25 15:26:41 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	d;

	d = 0;
	while (dest[d] && d < n)
		d++;
	i = d;
	while (src[d - i] && d + 1 < n)
	{
		dest[d] = src [d - i];
		d++;
	}
	if (i < n)
		dest[d] = '\0';
	return (i + ft_strlen(src));
}
