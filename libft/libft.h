/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-cecc <fdi-cecc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:19:37 by fdi-cecc          #+#    #+#             */
/*   Updated: 2024/10/04 11:11:28 by fdi-cecc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

// Check functions

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

// List functions

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

// Memory functions

void	*ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);

// Print functions

void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

// String functions

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, char const *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *hay, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

// extra

size_t	ft_word_count(char *s, char c);
int		ft_isspace(int c);
int		ft_atoi_base(const char *str, int base);
long	ft_atol(const char *s);
void	ft_freear(char **array);

// ft_printf

typedef struct s_flags
{
	int	hash;
	int	space;
	int	dot;
	int	plus;
	int	zero;
	int	minus;
	int	left;
	int	zerofill;
	int	precision;
	int	width;
}	t_flags;

int		ft_printf(const char *fmt, ...);

int		ft_parse(const char *str, va_list *args, int *i);
int		ft_processfmt(const char *str, va_list *args, t_flags flag);
void	ft_processflags(t_flags *flag, const char *str, int *i);

int		ft_printchar(char c, t_flags flag);

int		ft_printstr(const char *str, t_flags flag);
int		ft_printstrlen(const char *str);

int		ft_atoiptr(const char *str, int *adv);
void	ft_initflags(t_flags *flag);
int		ft_checkflags(char c, char *str);
int		ft_putcharlen(char c);

int		ft_printnum(long n, t_flags flag);
int		ft_putnbrlen(long n);

int		ft_printuns(unsigned long n, t_flags flag);

int		ft_printhex(int n, int upcase, t_flags flag);

int		ft_printptr(void *ptr, t_flags flag);

// Get next line + utils

# define BUFFER_SIZE 20

char	*get_next_line(int fd);

// char	*get_next_line(int fd);
// void	ft_newlist(t_list **list, int fd);
// void	ft_append(t_list **list, char *buffer, int fd);
// char	*ft_getline(t_list *list);
// void	ft_cleanlist(t_list **list);

// int		ft_newline(t_list *list);
// t_list	*ft_lastnode(t_list *list);
// int		ft_linelength(t_list *list);
// void	ft_copyline(t_list *list, char *str);
// void	ft_freelist(t_list **list, t_list *cleannode, char *buffer);

#endif