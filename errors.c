/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:03:51 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/04 17:54:42 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_error_handle(int errorcode)
{
	if (errorcode == ERR_STRUCT)
		printf("Error: invalid mlx data structure\n");
	if (errorcode == ERR_MALLOC)
		printf("Error: failed malloc\n");
	if (errorcode == ERR_INIT)
		printf("Error: faile init\n");
	if (errorcode == ERR_WIN)
		printf("Error: failed window\n");
	return (1);
}