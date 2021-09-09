/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:11:45 by talyx             #+#    #+#             */
/*   Updated: 2021/09/07 21:17:00 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl
{
	int		byte_read;
	int		fd;
	int		rp;
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

}				t_gnl;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
}				t_counter;

size_t				ft_strlcat(char *dst, const char *src, size_t size);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);

size_t				ft_strlen(const char *s);

char				*ft_strchr(const char *s, int c);

char				*ft_strrchr(const char *str, int ch);

char				*ft_strnstr(const char *big, const char *little,
						size_t len);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_atoi(const char *nptr);

int					ft_isspace(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isprint(int c);

int					ft_isalnum(int c);

int					ft_isdigit(int c);

int					ft_islower(int c);

int					ft_isupper(int c);

int					ft_toupper(int c);

int					ft_tolower(int c);

char				*ft_strcpy(char *dst, const char *src);

char				*ft_strdup(const char *s);

void				*ft_memset(void *s, int c, size_t n);

void				*ft_calloc(size_t nmemb, size_t size);

void				ft_bzero(void *s, size_t n);

void				*ft_memmove(void *dst, const void *src, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				**ft_split(char const *s, char c);

char				*ft_strncpy(char *dest, const char *src, size_t n);

char				*ft_itoa(int n);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_lstsize(t_list *lst);

t_list				*ft_lstnew(void *content);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstiter(t_list *lst, void (*f)(void *));

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstadd_front(t_list **lst, t_list *new);

void				ft_lstadd_back(t_list **lst, t_list *new);

int					ft_strequ(char *s1, char *s2);

char				**ft_ssplit(char const *s, char *set);

double				ft_atof(char *str);

int					ft_str_c_count(char *str, char c);

void				ft_strdel(char **as);

void				ft_putchar(char c);

void				ft_putnbr(int n);

void				ft_putstr(char *s);

char				**ft_split_clear(char **split);

void				error_exit(char *str);

int					get_next_line(int fd, char **line);


#endif