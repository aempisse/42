#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
// # include <mlx.h>
# include "minilibx/mlx.h"

# define WIDTH 640
# define HEIGHT 360

// j'ai remplacé le nom de la struct s_gest_scn par s_control pour plus de clareté
typedef struct	s_control
{
	int			menu;
	int			nbr_o;
	int			nbr_sp;
	int			ctm_1; // ca veut dire quoi ctm_1 ?
}				t_control;

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
	void		*win_scene;
	void		*win_control;
	t_image		*img;
	t_array		*sphere;
	t_array		*plane;
	t_control	*control;
	int			render;
}				t_env;

void			ft_load_file(int fd, t_env *env);
void			draw_control(t_env *env);
int				loop_hook(t_env *env);

#endif