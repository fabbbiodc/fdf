/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:57:16 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/06/28 18:05:26 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LINE_H
# define	LINE_H

# include	<stdio.h>
# include	<stdlib.h>
# include	"keys.h"
# define	HEIGHT 200
# define	WIDTH 200

typedef	struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
} t_mlx;

#endif
