#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "libft/libft.h"

# define WIDTH		1280
# define HEIGHT		700

# define DEF_COLORS	"0,255,64 ; 255,0,0"
# define DEF_PTDIST	70

typedef struct	s_image
{
	unsigned char	*data;
	void			*img;
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

typedef struct	s_env
{
	void			*mlx;
	void			*win;
	t_pt			offset;
	t_image			*img;
	t_array			*map;
	t_array			*color;
	double			pt_dist;
	double			max_z;
	double			min_z;
}				t_env;

int				ft_load_map(int fd, t_env *env);
void			ft_mapoffset(t_env *env);
void			ft_draw_map(t_env *env);
t_pt			ft_project_iso(t_pos pos);
t_array			*ft_new_color(char *input);
t_color			ft_atocolor(char *str);
void			ft_draw_point(t_env *env, t_pos pos);
void			ft_draw_line(t_env *env, t_pos p1, t_pos p2);
t_color			ft_get_color(t_array *gradient, double pos);
double			ft_posd(int min, int max, int pos);
int				ft_mixd(int a, int b, double pos);
void			ft_put_image(t_image *img, int pos, t_color color);

int				ft_parseint(t_buff *buff);
double			ft_parsedouble(t_buff *buff);
void			ft_parsespace(t_buff *buff);
void			ft_parsenot(t_buff *buff, const char *parse);


#endif