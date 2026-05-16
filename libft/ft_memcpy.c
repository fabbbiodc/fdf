/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:30:15 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/04/25 12:42:22 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*d;

	d = dest;
	if (!dest && !src)
		return (dest);
	while (n--)
	{
		*(unsigned char *)d++ = *(unsigned char *)src++;
	}
	return (dest);
}
