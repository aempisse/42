#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <mlx.h>
//# include "minilibx/mlx.h"

# define WIDTH 640
# define HEIGHT 360

typedef struct	s_gest
{
	int			menu;
	int			nbr_o;
	int			nbr_sp;
	int			ctm_1;
}				t_gest;

typedef struct	s_double3
{
	double		x;
	double		y;
	double		z;
}				t_double3;

typedef struct	s_plane
{
	t_double3	pos;
}				t_plane;

typedef struct	s_sphere
{
	t_double3	pos;
	double		radius;
	// t_color		color;
}				t_sphere;

typedef struct	s_env
{
	void		*mlx;
	void		*win_scn;
	void		*win_gest_scn;
	t_image		*img;
	t_array		*sphere;
	t_array		*plane;
	t_gest		*gest;
	// int			render;
}				t_env;

void			ft_load_file(int fd, t_env *env);
void			draw_gest_scn(t_env *env);
int				expose_hook(t_env *env);

#endif