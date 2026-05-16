/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:27:34 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/04/30 17:11:49 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	k = ft_strlen(s2);
	new = malloc(((i + k + 1)) * (sizeof(char)));
	if (!new)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		new[i + k] = s2[k];
		k++;
	}
	new[i + k] = '\0';
	return (new);
}
