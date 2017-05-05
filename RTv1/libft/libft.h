/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 20:04:27 by aempisse          #+#    #+#             */
/*   Updated: 2017/05/02 12:40:11 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <errno.h>

# define OPEN_FLAG S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

# define GNL_BUFF_SIZE 64

# define PT(x,y)		((t_pt){(x), (y)})
# define POS(x,y,z)		((t_pos){(x), (y), (z)})
# define ROUND(n)		((int)(0.5 + (n)))
# define DOWN(n)		((int)(n))
# define ABS(a)			(((a) < 0) ? -(a) : (a))
# define MIN(a,b)		(((a) < (b)) ? (a) : (b))
# define MAX(a,b)		(((a) > (b)) ? (a) : (b))
# define AG(t,a,i)		((t)(((t_array*)(a))->data[i]))
# define TG(t,b,i)		(*(t*)(((t_tab*)b)->data + (((t_tab*)b)->size * (i))))

typedef struct	s_pt
{
	int				x;
	int				y;
}				t_pt;

typedef struct	s_pos
{
	double			x;
	double			y;
	double			z;
}				t_pos;

typedef struct	s_array
{
	void			**data;
	int				length;
	int				alloc_length;
}				t_array;

typedef struct	s_tab
{
	unsigned char	*data;
	int				length;
	int				bytes;
	int				alloc_bytes;
	int				size;
}				t_tab;

typedef struct	s_buff
{
	char			*data;
	int				i;
	int				length;
}				t_buff;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;


typedef struct	s_image
{
	unsigned char	*data;
	char			*img;
	int				width;
	int				height;
	int				l_size;
	int				opp;
	int				endian;
}				t_image;

typedef struct	s_argb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}				t_argb;

typedef union	u_color
{
	t_argb			b;
	unsigned int	u;
	int				i;
}				t_color;


typedef struct	s_gnlfd
{
	char			*buff;
	int				fd;
	int				length;
	int				offset;
	int				i;
	struct s_gnlfd	*next;
}				t_gnlfd;

void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy (void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen (const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *dst, const char *src);
char				*ft_strncat(char *dst, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isnumber(const char *str);
int					ft_isrange(int n, int start, int end);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isspace(int c);
int					ft_iswhite(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				**ft_strsplit(const char *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(const char *str);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					get_next_line(int const fd, t_buff *line);
void				ft_error(const char *str);

t_array				*ft_array_new(void);
void				ft_array_add(t_array *array, void *add);
void				ft_array_clr(void *array, void (*f)(void *data));
int					ft_array_ext(t_array *array, int need);
void				ft_array_ini(t_array *array);
void				ft_array_kill(void *array, void (*f)(void *data));

t_tab				*ft_tab_new(int size);
void				ft_tab_add(t_tab *tab, const void *add);
void				ft_tab_addn(t_tab *tab, const void *add, int n);
int					ft_tab_ext(t_tab *tab, int need);
void				ft_tab_ini(t_tab *tab, int size);
void				ft_tab_kill(void *tab);

int					ft_parse_int(t_buff *buff);
void				ft_parse_space(t_buff *buff);
double				ft_parse_double(t_buff *buff);
void				ft_parse_not(t_buff *buff, const char *parse);

#endif
