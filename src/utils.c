/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:43 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/14 20:02:18 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	while (n--)
		*s++ = (unsigned char)c;
	return (str);
}
