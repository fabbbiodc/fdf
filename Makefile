# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:51:31 by fdi-cecc          #+#    #+#              #
#    Updated: 2024/07/30 10:29:36 by fdi-cecc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= 	fdf

SRC_DIR		:=	src
INC_DIR		:=	inc

SRC_FILES	:= 	fdf.c draw.c free.c render.c rotations.c cam.c  map.c parse.c color.c init.c panel.c \
				controls.c placement.c dda.c projections.c

SRC			:=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ  		:=	$(SRC:.c=.o)

LIBFTDIR	:=	libft
LIBFT		:=	$(LIBFTDIR)/libft.a

CC			:= 	cc
CFLAGS 		:= 	-Wall -Werror -Wextra
RM			:=	/bin/rm -f

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MINILIBXDIR := 	minilibx_linux
	MINILIBX	:= 	$(MINILIBXDIR)/libmlx.a
	LINKEDIR	:= 	-L$(MINILIBXDIR) -L$(LIBFTDIR)
	LIBS		:=	-lmlx -lX11 -lXext -lft -lm
	INCLUDES	:=	-I$(INC_DIR) -I$(MINILIBXDIR) -I$(LIBFTDIR)
else
	MINILIBXDIR := 	minilibx_opengl
	MINILIBX	:= 	$(MINILIBXDIR)/libmlx.a
	LINKEDIR	:= 	-L$(MINILIBXDIR) -L$(LIBFTDIR)
	LIBS		:=	-lmlx -framework OpenGL -framework AppKit -lft -lm
	INCLUDES	:=	-I$(INC_DIR) -I$(MINILIBXDIR) -I$(LIBFTDIR)
endif

all:		$(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $(OBJ) $(LINKEDIR) $(LIBS)

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS)  $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MINILIBXDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(MINILIBXDIR)

re: fclean all

.PHONY:
	all clean fclean re
