/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:56:18 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/12/08 18:36:47 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ft_is_control_key:
Checks if the given key is a recognized control key for the application.
// Called from:
ft_keyreact
// Output:
Returns 1 if the key is a control key, 0 otherwise.*/
int	ft_is_control_key(int key)
{
	return (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT || key == KEY_PLU || key == KEY_MIN
		|| key == KEY_A || key == KEY_D || key == KEY_P
		|| key == KEY_O || key == KEY_L || key == KEY_W
		|| key == KEY_S || key == KEY_Q || key == KEY_E
		|| key == KEY_C);
}

/* ft_handle_move:
Processes movement-related key inputs and updates camera position or rotation.
// Called from:
ft_cam_control
// Output:
Modifies camera parameters in the fdf structure based on key input.*/
void	ft_handle_move(int key, t_mlx *fdf)
{
	if (key == KEY_UP)
		fdf->cam->alpha += ROTATION;
	else if (key == KEY_DOWN)
		fdf->cam->alpha -= ROTATION;
	else if (key == KEY_LEFT)
		fdf->cam->beta -= ROTATION;
	else if (key == KEY_RIGHT)
		fdf->cam->beta += ROTATION;
	else if (key == KEY_Q)
		fdf->cam->spin_angle += ROTATION;
	else if (key == KEY_E)
		fdf->cam->spin_angle -= ROTATION;
	if (key == KEY_D)
		fdf->cam->x_move -= MOVE;
	else if (key == KEY_A)
		fdf->cam->x_move += MOVE;
	else if (key == KEY_S)
		fdf->cam->y_move += MOVE;
	else if (key == KEY_W)
		fdf->cam->y_move -= MOVE;
}

/* ft_handle_zoom:
Processes zoom-related key inputs and adjusts the map scale.
// Called from:
ft_cam_control
// Output:
Modifies zoom-related parameters in the fdf structure.*/
void	ft_handle_zoom(int key, t_mlx *fdf)
{
	if (key == KEY_PLU)
	{
		fdf->cam->theta += ZOOM;
	}
	else if (key == KEY_MIN)
	{
		fdf->cam->theta -= ZOOM;
		if (fdf->cam->theta < ZOOM)
			fdf->cam->theta = ZOOM;
	}
}

/* ft_cam_control:
Manages all camera control operations based on user input.
// Called from:
ft_keyreact
// Output:
Updates various camera and map parameters in the fdf structure.*/
void	ft_cam_control(int key, t_mlx *fdf)
{
	ft_handle_zoom(key, fdf);
	ft_handle_move(key, fdf);
	if (key == KEY_P)
		ft_toggle_projection(fdf);
	else if (key == KEY_O)
		fdf->cam->proj_distance += 50.0;
	else if (key == KEY_L)
		fdf->cam->proj_distance -= 50.0;
	else if (key == KEY_C)
		ft_toggle_color(fdf);
	fdf->cam->spin_angle = fmod(fdf->cam->spin_angle, 2 * M_PI);
}

/* ft_toggle_projection:
Switches between different projection modes (isometric, orthographic, etc.).
// Called from:
ft_cam_control
// Output:
Updates the projection mode in the fdf structure and resets
relevant parameters.*/
void	ft_toggle_projection(t_mlx *fdf)
{
	if (fdf->cam->proj == PROJ_ISO)
	{
		fdf->cam->proj = PROJ_ORTHO;
		fdf->cam->alpha = 0;
		fdf->cam->beta = 0;
		fdf->cam->gamma = 0;
	}
	else if (fdf->cam->proj == PROJ_ORTHO)
		fdf->cam->proj = PROJ_1PT;
	else if (fdf->cam->proj == PROJ_1PT)
		fdf->cam->proj = PROJ_2PTS;
	else if (fdf->cam->proj == PROJ_2PTS)
		fdf->cam->proj = PROJ_ISO;
	ft_center_map(fdf);
}
