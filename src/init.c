/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:15:19 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 19:27:11 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_create_image:
Creates a new MLX image for rendering.
// Called from:
ft_init_image
// Output:
Creates a new image and allocates memory for image attributes.*/
int	ft_create_image(t_mlx *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		return (0);
	fdf->img_att = (t_img *)malloc(sizeof(t_img));
	if (!fdf->img_att)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = NULL;
		return (0);
	}
	return (1);
}

/* ft_cam_init:
Initializes the camera structure with default values.
// Called from:
ft_fdf_init
// Output:
Allocates memory for the camera structure and sets initial parameters.*/
int	ft_cam_init(t_mlx *fdf)
{
	fdf->cam = (t_cam *)malloc(sizeof(t_cam));
	if (!fdf->cam)
		return (EXIT_FAILURE);
	ft_cam_params(fdf);
	return (EXIT_SUCCESS);
}

/* ft_init_image:
Initializes or reinitializes the MLX image for rendering.
// Called from:
ft_fdf_init, ft_keyreact (indirectly through ft_cam_control)
// Output:
Creates a new image and sets up its attributes.*/
int	ft_init_image(t_mlx *fdf)
{
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->img_att)
		free(fdf->img_att);
	fdf->img = NULL;
	fdf->img_att = NULL;
	if (!ft_create_image(fdf))
		return (0);
	fdf->img_att->addr = mlx_get_data_addr(fdf->img, &fdf->img_att->bpp,
			&fdf->img_att->linesize, &fdf->img_att->endian);
	if (!fdf->img_att->addr)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		free(fdf->img_att);
		fdf->img = NULL;
		fdf->img_att = NULL;
		return (0);
	}
	return (1);
}

/* ft_fdf_init:
Initializes the entire FdF program structure.
// Called from:
main
// Output:
Sets up MLX, creates window,
initializes image, parses map, and sets up camera.*/
int	ft_fdf_init(t_mlx *fdf, char *map_file)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF fdi-cecc");
	if (!fdf->win)
		return (0);
	if (!ft_init_image(fdf))
		return (0);
	fdf->map = ft_parse_map(map_file);
	if (!fdf->map || ft_cam_init(fdf) != EXIT_SUCCESS)
		return (0);
	ft_cam_params(fdf);
	ft_cam_fit(fdf);
	return (1);
}
