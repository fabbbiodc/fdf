/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:09:53 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/07/27 23:59:45 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# define WIN_HEIGHT	1080
# define WIN_WIDTH	1920
# define DEFAULT_COLOR 0x0000FF00
# define ROTATION 0.05
# define ZOOM 1
# define MOVE 5
# define BUFFER_SIZE 20
# define MARGIN 100
# define PROJECTION_DISTANCE 1000.0

// panel

# define PANEL_WIDTH 300
# define PANEL_HEIGHT 350
# define PANEL_MARGIN 40
# define PANEL_BACKGROUND 0x80000000
# define PANEL_TEXT_COLOR 0xFFFFFF
# define PANEL_INFO_COLOR 0xAAAAAA
# define PANEL_LOGO_COLOR 0x00FF00

// boundaries

#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

// errors

# define ERR_STRUCT 2
# define ERR_MALLOC	3
# define ERR_INIT	4
# define ERR_WIN	5
# define ERR_IMG	6
# define ERR_DRAW	7
# define ERR_CAM	8
# define ERR_MAP	9

// projections

# define PROJ_ISO	2
# define PROJ_ORTHO	3
# define PROJ_1PT 	4
# define PROJ_2PTS	5

// angles radians doubles

# define RAD_0      0.0
# define RAD_30     0.52359877559829887307
# define RAD_45     0.78539816339744830962
# define RAD_60     1.04719755119659774615
# define RAD_90     1.57079632679489661923
# define RAD_120    2.09439510239319549230
# define RAD_135    2.35619449019234492884
# define RAD_150    2.61799387799149436538
# define RAD_180    3.14159265358979323846
# define RAD_270    4.71238898038468985769
# define RAD_360    6.28318530717958647692

# define RAD_TO_DEG 57.29577951308232087679
# define DEG_TO_RAD 0.01745329251994329576

# define SQRT_2      1.41421356237309504880
# define SQRT_3      1.73205080756887729352

#endif