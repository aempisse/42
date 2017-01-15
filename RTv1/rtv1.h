#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <mlx.h>
//# include "minilibx/mlx.h"
# include <math.h>

# define WIDTH 512
# define HEIGHT 512
# define FOV 51.52

	/* Key pour Linux 
//# define KEY_ESC 65307*/

	/*Key pour Mac */
# define KEY_ESC 53
# define KEY_ENTER 36
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_NEG 24
# define KEY_M 41


# define PI 3.14159265

typedef struct	s_double2
{
	double		x;
	double		y;
}				t_double2;

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
}				t_sphere;

typedef struct	s_camera
{
	t_double3	pos;
	t_double3	dir;
}				t_camera;

typedef struct	s_control
{
	int			menu;
	int			nbr_max;
	int			nbr_sp;
	int			ctm_1;
	int			i;
	int			mod;
	int			neg;
	int			stop_add;
	double		num;
	char		*name_obj;
}				t_control;

typedef struct	s_env
{
	void		*mlx;
	void		*win_scene;
	void		*win_control;
	t_image		*img;
	t_array		*sphere;
	t_array		*plane;
	t_camera	camera;
	t_control	*control;
	double		fov;
	int			render;
}				t_env;

void			ft_load_file(int fd, t_env *env);
void			render(t_env *env);
void			raytracer(t_env *en, int x, int y);
int				intersect(t_env *env, t_double3 dir, t_sphere *sphere);
double			dot_product(t_double3 vec1, t_double3 vec2);
t_double3		normalize(t_double3 vec);
void			draw_control(t_env *env);
int				loop_hook(t_env *env);
int				key_hook(int keycode, t_env *env);
void			ft_draw_small_arrow(t_env *env);
void			draw_square(t_env *env);
void			ft_draw_left_arrow(t_env *env);
void			ft_draw_right_arrow(t_env *env);
void			draw_value(t_env *env);
int				key_obj_menu(int keycode, t_env *env);
int				key_obj_in(int keycode, t_env *env);
char			*search_type_obj(int c);
void			draw_plane_value(t_env *env);
void			draw_sphere_value(t_env *env);
void			init_new_obj(t_env *env);
int				key_new_obj_in(int keycode, t_env *env);

#endif