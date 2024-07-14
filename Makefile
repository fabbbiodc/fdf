# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:51:31 by fdi-cecc          #+#    #+#              #
#    Updated: 2024/07/14 21:03:42 by fdi-cecc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= 	fdf

SRC_DIR		:=	src
INC_DIR		:=	inc

SRC_FILES	:= 	fdf.c drawline.c errors.c utils.c render.c rotations.c cam.c get_next_line.c get_next_line_utils.c

SRC			:=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ  		:=	$(SRC:.c=.o)

MINILIBXDIR := 	minilibx_linux
MINILIBX	:= 	$(MINILIBXDIR)/libmlx.a

CC			:= 	cc
CFLAGS 		:= 	-Wall -Werror -Wextra
FSANITIZE	:=	-fsanitize=address -g #to remove
INCLUDES	:=	-I$(INC_DIR) -I$(MINILIBXDIR)
LINKEDIR	:= 	-L$(MINILIBXDIR)
LIBS		:=	-lmlx -lX11 -lXext
RM			:=	/bin/rm -f

all:		$(NAME)

$(NAME): $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $(OBJ) $(FSANITIZE) $(LINKEDIR) $(LIBS)

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR)

%.o: %.c
	$(CC) $(CFLAGS)  $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MINILIBXDIR) clean

re: fclean all

.PHONY:
	all clean fclean re
