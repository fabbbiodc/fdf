/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:24:49 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/04/30 13:45:05 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	k;
	size_t	s_len;

	i = start;
	k = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > s_len)
		len = 0;
	if (len >= (s_len - start))
		len = s_len - start;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < s_len && k < len)
	{
		new[k] = s[i];
		k++;
		i++;
	}
	new[k] = '\0';
	return (new);
}
