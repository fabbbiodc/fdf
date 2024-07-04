# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:51:31 by fdi-cecc          #+#    #+#              #
#    Updated: 2024/07/04 17:55:53 by fdi-cecc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= 	fdf

SRC  		:= 	fdf.c drawline.c errors.c utils.c

OBJ  		:=	$(SRC:.c=.o)

MINILIBXDIR := 	minilibx_linux
MINILIBX	:= 	$(MINILIBXDIR)/libmlx.a

CC			:= 	cc
CFLAGS 		:= 	-Wall -Werror -Wextra
FSANITIZE	:=	-fsanitize=address -g #to remove
LINKEDIR	:= 	-L$(MINILIBXDIR)
LIBS		:=	-lmlx -lX11 -lXext
RM			:=	/bin/rm -f

all:		$(NAME)

$(NAME): $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $(OBJ) $(FSANITIZE) $(LINKEDIR) $(LIBS)

$(MINILIBX):
	$(MAKE) -C $(MINILIBXDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MINILIBXDIR) clean

re: fclean all

.PHONY:
	all clean fclean re
