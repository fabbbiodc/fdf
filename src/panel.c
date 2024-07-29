/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:12 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/29 18:14:09 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pnl_txt(t_mlx *fdf, t_pnt *p, char *str, int color)
{
	mlx_string_put(fdf->mlx, fdf->win, p->x, p->y, color, str);
}

void	ft_panel_draw(t_mlx *fdf)
{
	t_pnt	p;

	p.x = PNL_MARGIN;
	p.y = PNL_MARGIN;
	ft_pnl_txt(fdf, &p, "    ______    ________", PNL_LOGO_COLOR);
	p.y += 15;
	ft_pnl_txt(fdf, &p, "   / ____/___/ / ____/", PNL_LOGO_COLOR);
	p.y += 15;
	ft_pnl_txt(fdf, &p, "  / /_  / __  / /_    ", PNL_LOGO_COLOR);
	p.y += 15;
	ft_pnl_txt(fdf, &p, " / __/ / /_/ / __/    ", PNL_LOGO_COLOR);
	p.y += 15;
	ft_pnl_txt(fdf, &p, "/_/    \\__,_/_/       ", PNL_LOGO_COLOR);
	p.y += 30;
	ft_pnl_txt(fdf, &p, "fdi-cecc // 42Berlin", PNL_TEXT_COLOR);
	p.y += 30;
	ft_display_map_info(fdf, &p);
	ft_display_controls(fdf, &p);
}

void	ft_display_map_info(t_mlx *fdf, t_pnt *p)
{
	char	*str;

	str = ft_strjoin("Map size: ", ft_itoa(fdf->map->width));
	str = ft_strjoin(str, "x");
	str = ft_strjoin(str, ft_itoa(fdf->map->height));
	ft_pnl_txt(fdf, p, str, PNL_INFO_COLOR);
	free(str);
	p->y += 20;
	str = ft_strjoin("Projection: ",
			ft_get_projection_name(fdf->cam->proj));
	ft_pnl_txt(fdf, p, str, PNL_INFO_COLOR);
	free(str);
	p->y += 20;
	str = ft_strjoin("Zoom: ", ft_itoa((int)(fdf->cam->theta * 100)));
	ft_pnl_txt(fdf, p, str, PNL_INFO_COLOR);
	free(str);
	p->y += 30;
}

void	ft_display_controls(t_mlx *fdf, t_pnt *p)
{
	ft_pnl_txt(fdf, p, "Controls:", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "ESC: Exit", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "Arrows: Rotate", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "+/-: Zoom", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "WASD: Move", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "P: Change projection", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "Q/E: Spin", PNL_TEXT_COLOR);
	p->y += 20;
	ft_pnl_txt(fdf, p, "C: Change color", PNL_TEXT_COLOR);
}

const char	*ft_get_projection_name(int projection)
{
	if (projection == PROJ_ISO)
		return ("Isometric");
	if (projection == PROJ_ORTHO)
		return ("Orthogonal");
	if (projection == PROJ_1PT)
		return ("1-Point perspective");
	if (projection == PROJ_2PTS)
		return ("2-Points perspective");
	return ("Unknown");
}
