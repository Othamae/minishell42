/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:06 by vconesa-          #+#    #+#             */
/*   Updated: 2024/07/27 22:21:37 by vconesa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>

// Part 1
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
// Part 2
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int nbr);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
// Bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// FT_PRINTF
# ifndef BASE10
#  define BASE10 "0123456789"
# endif

# ifndef BASE16LOWER
#  define BASE16LOWER "0123456789abcdef"
# endif

# ifndef BASE16UPPER
#  define BASE16UPPER "0123456789ABCDEF"
# endif

typedef struct s_flags
{
	int	left;
	int	plus;
	int	space;
	int	hash;
	int	zero;
	int	width;
	int	precision;
	int	specifier;
}	t_flags;

typedef struct s_data
{
	const char	*s;
	va_list		args;
	t_flags		flags;
	int			chars_written;
	int			upper;
}	t_data;

int			ft_printf(const char *format, ...);
int			ft_isflag(int c);
int			ft_parse_format(t_data	*data);
int			ft_render_format(t_data *data);
int			ft_print_s(const char *str, int precision);

int			ft_print_char(int c, t_data	*data);
int			ft_print_c(char c);
int			ft_print_str(const char *str, t_data	*data);
int			ft_pad_width(int total_width, int size, int zero);
int			ft_print_int(int n, t_data	*data);
int			ft_print_u_base(unsigned int n, char *base, t_data *data);
int			ft_print_nbr_base(int n, char *base, t_data *data);
int			ft_print_ptr(unsigned long long int n, char *base, t_data *data);
char		*ft_utoa(unsigned int num);
char		*ft_xtoa(unsigned long int num, int is_upper);

// GET_NEXT_LINE
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_gnl_list
{
	char				*str_buff;
	struct s_gnl_list	*next;
}	t_gnl_list;

char		*get_next_line(int fd);
void		refresh_list(t_gnl_list **list);
void		fill_list(t_gnl_list *last_node, char *buff, t_gnl_list *new_node);
int			found_newline(t_gnl_list *list);
void		create_list(t_gnl_list **list, int fd);
char		*found_line(t_gnl_list *list);
t_gnl_list	*get_last_node(t_gnl_list *list);
void		append(t_gnl_list **list, char *buff, int fd);
int			get_line_len(t_gnl_list *list);
void		copy_str(t_gnl_list *list, char *str);
void		free_list(t_gnl_list **list, t_gnl_list *new_node,
				char *buff, int free_only);

#endif