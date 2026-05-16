/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:36:50 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/05/02 00:14:54 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	len;
	long	nbr;
	char	*array;

	len = ft_length(n);
	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[len] = 0;
	if (nbr == 0)
		array[0] = '0';
	else
	{
		while (len--, nbr != 0)
		{
			array[len] = (nbr % 10) + '0';
			nbr = (nbr - (nbr % 10)) / 10;
		}
		if (n < 0)
			array[len] = '-';
	}
	return (array);
}
