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

MINILIBXDIR := 	minilibx_linux
MINILIBX	:= 	$(MINILIBXDIR)/libmlx.a

LIBFTDIR	:=	libft
LIBFT		:=	$(LIBFTDIR)/libft.a

CC			:= 	cc
CFLAGS 		:= 	-Wall -Werror -Wextra
INCLUDES	:=	-I$(INC_DIR) -I$(MINILIBXDIR) -I$(LIBFTDIR)
LINKEDIR	:= 	-L$(MINILIBXDIR) -L$(LIBFTDIR)
LIBS		:=	-lmlx -lX11 -lXext -lft -lm
RM			:=	/bin/rm -f

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
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MINILIBXDIR) clean
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY:
	all clean fclean re
