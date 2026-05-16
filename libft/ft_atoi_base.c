/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:33:58 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/19 19:00:35 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convert_digit(char c, int base)
{
	int	digit;

	if (ft_isdigit(c))
		digit = c - '0';
	else if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	else
		return (-1);
	if (digit < base)
		return (digit);
	return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	digit;
	int	sign;

	result = 0;
	digit = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		digit = ft_convert_digit(*str, 16);
		if (digit == -1)
			break ;
		result = result * base + digit;
		str++;
	}
	return (result * sign);
}
