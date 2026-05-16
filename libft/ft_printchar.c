/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:54:52 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/16 17:55:39 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c, t_flags flag)
{
	int	i;

	i = 0;
	while (i + 1 < flag.width)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putchar(c);
	i++;
	while (i < flag.left)
	{
		ft_putchar(' ');
		i++;
	}
	return (i);
}
