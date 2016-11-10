#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <time.h>

# define WIDTH 1280
# define HEIGHT 720

typedef	struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef	struct	s_env
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_array		*map;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_pos;
	t_pt		map_pos;
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_vector	step;
	double		camera;
	t_vector	time;
	int			render;
}				t_env;

int				loop_hook(t_env *env);
int				expose_hook(t_env *env);
int				key_hook(int keycode, t_env *env);
void			raycasting(t_env *env);

#endif
