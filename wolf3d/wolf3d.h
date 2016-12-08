#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <math.h>
# include <time.h>

# define WIDTH 1280
# define HEIGHT 720

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define KEY_PRESS 2
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE 3
# define KEY_RELEASE_MASK (1L<<1)

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

# define MOVE_SPEED 3 //0.000009
# define ROT_SPEED 1 //0.000006
# define HALF_PI 1.57079632

# define WEST 0
# define EAST 1
# define SOUTH 2
# define NORTH 3

typedef struct s_rect
{
	int			a;
	int			b;
	int			c;
	int			d;
}				t_rect;

typedef struct	s_key
{
	int			up;
	int			down;
	int			left;
	int			right;
}				t_key;

typedef	struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef	struct	s_env
{
	void		*mlx;
	void		*win;
	void		*win2;
	t_image		*img;
	// t_array		*map;
	int			**map;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_pos;
	t_pt		map_pos;
	t_vector	ray_dir;
	int			side;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_vector	step;
	double		camera;
	t_key		key;
	int			state;
	double		old_time;
	double		new_time;
	t_color		(*color)(struct s_env*, int, int, int);
	int			color_id;
	int			render;
}				t_env;

int				ft_load_map(int fd, t_env *env);
int				loop_hook(t_env *env);
int				expose_hook(t_env *env);
int				key_press(int keycode, t_env *env);
int				key_hook(int keycode, t_env *env);
int				key_release(int keycode, t_env *env);
void			raycasting(t_env *env);
void			minimap(t_env *env);
void			ft_put_image(t_image *img, int pos, t_color color);
void			switch_color(t_env *env);
t_color			color0(t_env *env, int y, int draw_start, int draw_end);
t_color			color1(t_env *env, int y, int draw_start, int draw_end);
void			change_state(t_env *env);
void			unlocked_messages(t_env *env);

#endif
