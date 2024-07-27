/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:12 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/28 01:07:37 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    ft_draw_transparent_rectangle(t_mlx *fdf, int x, int y, int width, int height, int color)
{
    int i;
    int j;
    int pixel;
    int alpha;
    int src_color;
    int dst_color;

    alpha = (color >> 24) & 0xFF;
    i = y;
    while (i < y + height)
    {
        j = x;
        while (j < x + width)
        {
            pixel = (i * fdf->img_att->linesize) + (j * (fdf->img_att->bpp / 8));
            src_color = color & 0x00FFFFFF;
            dst_color = *(unsigned int*)(fdf->img_att->addr + pixel);
            *(unsigned int*)(fdf->img_att->addr + pixel) = 
                ((((src_color & 0xFF0000) * alpha + (dst_color & 0xFF0000) * (255 - alpha)) >> 8) & 0xFF0000) |
                ((((src_color & 0x00FF00) * alpha + (dst_color & 0x00FF00) * (255 - alpha)) >> 8) & 0x00FF00) |
                ((((src_color & 0x0000FF) * alpha + (dst_color & 0x0000FF) * (255 - alpha)) >> 8) & 0x0000FF);
            j++;
        }
        i++;
    }
}

void    ft_panel_text(t_mlx *fdf, int x, int y, char *str, int color)
{
    mlx_string_put(fdf->mlx, fdf->win, x, y, color, str);
}
void	ft_panel_logo(t_mlx *fdf, int x, int y)
{
    ft_panel_text(fdf, x, y, "    ______    ________", PANEL_LOGO_COLOR);
    ft_panel_text(fdf, x, y + 15, "   / ____/___/ / ____/", PANEL_LOGO_COLOR);
    ft_panel_text(fdf, x, y + 30, "  / /_  / __  / /_    ", PANEL_LOGO_COLOR);
    ft_panel_text(fdf, x, y + 45, " / __/ / /_/ / __/    ", PANEL_LOGO_COLOR);
    ft_panel_text(fdf, x, y + 60, "/_/    \\__,_/_/       ", PANEL_LOGO_COLOR);
}

const char    *ft_get_color_name(int color_scheme)
{
    if (color_scheme == 0)
        return ("White");
    if (color_scheme == 1)
        return ("Red");
    if (color_scheme == 2)
        return ("Green");
    if (color_scheme == 3)
        return ("Blue");
    if (color_scheme == 4)
        return ("Yellow");
    if (color_scheme == 5)
        return ("Magenta");
    if (color_scheme == 6)
        return ("Cyan");
	if (color_scheme == 7)
        return ("Purple");
    return ("Unknown");
}

void    ft_panel_content(t_mlx *fdf)
{
    int y;
    char *str;

    y = PANEL_MARGIN;
    ft_panel_logo(fdf, PANEL_MARGIN, y);
    y += 90;

    ft_panel_text(fdf, PANEL_MARGIN, y, "fdi-cecc // 42Berlin", PANEL_TEXT_COLOR);
    y += 30;

    str = ft_strjoin("Map size: ", ft_itoa(fdf->map->width));
    str = ft_strjoin(str, "x");
    str = ft_strjoin(str, ft_itoa(fdf->map->height));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Projection: ", ft_get_projection_name(fdf->cam->projection));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

	str = ft_strjoin("Color: ", ft_get_color_name(fdf->cam->color_scheme));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Zoom: ", ft_itoa((int)(fdf->cam->theta * 100)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 30;

    ft_panel_text(fdf, PANEL_MARGIN, y, "Controls:", PANEL_TEXT_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "ESC: Exit", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "Arrows: Rotate", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "+/-: Zoom", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "WASD: Move", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "P: Change projection", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "Q/E: Spin", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "C: Change color", PANEL_INFO_COLOR);
}

const char *ft_get_projection_name(int projection)
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

void	ft_panel_draw(t_mlx *fdf)
{
	ft_printf("panel draw reached\n");
	ft_panel_content(fdf);
}

