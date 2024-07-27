/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:22:12 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/28 00:34:54 by fdi-cecc         ###   ########.fr       */
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

void    ft_panel_content(t_mlx *fdf)
{
    char *str;
    int y;
    const char *projection_name;

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

    if (fdf->cam->projection == PROJ_ISO)
        projection_name = "Isometric";
    else if (fdf->cam->projection == PROJ_ORTHO)
        projection_name = "Orthographic";
    else if (fdf->cam->projection == PROJ_1PT)
        projection_name = "1-Point";
    else
        projection_name = "2-Point";
    str = ft_strjoin("Projection: ", projection_name);
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Zoom: ", ft_itoa((int)(fdf->cam->theta * 100)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Rotation X: ", ft_itoa((int)(fdf->cam->alpha * RAD_TO_DEG)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Rotation Y: ", ft_itoa((int)(fdf->cam->beta * RAD_TO_DEG)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Rotation Z: ", ft_itoa((int)(fdf->cam->gamma * RAD_TO_DEG)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 20;

    str = ft_strjoin("Spin: ", ft_itoa((int)(fdf->cam->spin_angle * RAD_TO_DEG)));
    ft_panel_text(fdf, PANEL_MARGIN, y, str, PANEL_INFO_COLOR);
    free(str);
    y += 30;

    ft_panel_text(fdf, PANEL_MARGIN, y, "Controls:", PANEL_TEXT_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "ESC: Exit", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "Arrow keys: Rotate X/Y", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "+/-: Zoom in/out", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "W/S: Move up/down", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "A/D: Move left/right", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "P: Change projection", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "O/L: Adjust projection distance", PANEL_INFO_COLOR);
    y += 20;
    ft_panel_text(fdf, PANEL_MARGIN, y, "Q/E: Spin left/right", PANEL_INFO_COLOR);
}

void	ft_panel_draw(t_mlx *fdf)
{
	ft_printf("panel draw reached\n");
	ft_panel_content(fdf);
}

