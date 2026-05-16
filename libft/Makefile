# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 17:57:36 by fdi-cecc          #+#    #+#              #
#    Updated: 2024/10/04 11:11:37 by fdi-cecc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        := libft.a
CC        := cc
FLAGS    := -Wall -Wextra -Werror 

SRCS        :=      ft_isalnum.c \
                          ft_isalpha.c \
                          ft_isascii.c \
                          ft_isdigit.c \
                          ft_isprint.c \
                          ft_lstadd_back.c \
                          ft_lstadd_front.c \
                          ft_lstclear.c \
                          ft_lstdelone.c \
                          ft_lstiter.c \
                          ft_lstlast.c \
                          ft_lstmap.c \
                          ft_lstnew.c \
                          ft_lstsize.c \
                          ft_bzero.c \
                          ft_calloc.c \
                          ft_memchr.c \
                          ft_memcmp.c \
                          ft_memcpy.c \
                          ft_memmove.c \
                          ft_memset.c \
                          ft_putchar.c \
                          ft_putchar_fd.c \
                          ft_putendl_fd.c \
                          ft_putnbr_fd.c \
                          ft_putstr_fd.c \
                          ft_atoi.c \
                          ft_itoa.c \
                          ft_split.c \
                          ft_strchr.c \
                          ft_strdup.c \
                          ft_striteri.c \
                          ft_strjoin.c \
                          ft_strlcat.c \
                          ft_strlcpy.c \
                          ft_strlen.c \
                          ft_strmapi.c \
                          ft_strncmp.c \
                          ft_strnstr.c \
                          ft_strrchr.c \
                          ft_strtrim.c \
                          ft_substr.c \
                          ft_tolower.c \
                          ft_toupper.c \
                          get_next_line.c \
                          ft_printchar.c \
                          ft_printhex.c \
                          ft_printnum.c \
                          ft_printptr.c \
                          ft_printstr.c \
                          ft_printuns.c \
                          ft_parse.c \
                          ft_printf.c \
                          ft_tools.c \
						  ft_word_count.c\
						  ft_isspace.c\
						  ft_atoi_base.c\
						  ft_atol.c\
						  ft_freear.c
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			ar rcs ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


