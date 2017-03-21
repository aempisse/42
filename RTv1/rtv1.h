#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
// # include <mlx.h>
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

# define WIDTH 1280
# define HEIGHT 960
# define FOV 30
# define DEPTH_MAX 5

	 // Key pour Linux 
# define KEY_ESC 65307

	// Key pour Mac 
// # define KEY_ESC 53
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

# define DIFFUSE_GLOSSY 0
# define REFLECTION 1
# define REFLECTION_AND_REFRACTION 2

# define BIAS 0.00001

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

typedef struct	s_surface
{
	double		distance;
	t_double3	p_hit;
	t_double3	n_hit;
	t_double3	color;
	double		ior;
	int			material;
}				t_surface;

typedef struct	s_light
{
	t_double3	pos;
	t_double3	color;
}				t_light;

typedef struct	s_plane
{
	t_double3	pos;
	t_double3	normal;
	t_double3	color;
	double		ior;
	int			material;
}				t_plane;

typedef struct	s_sphere
{
	t_double3	pos;
	double		radius;
	t_double3	color;
	double		ior;
	int			material;
}				t_sphere;

typedef struct	s_objects
{
	t_array		*spheres;
	t_array		*planes;
	t_array		*lights;
}				t_objects;

typedef struct	s_vector
{
	t_double3	pos;
	t_double3	dir;
}				t_vector;

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
	t_objects	*objects;
	t_vector	camera;
	t_control	*control;
	int			render;
}				t_env;

int				loop_hook(t_env *env);
int				key_hook(int keycode, t_env *env);

void			ft_load_file(int fd, t_env *env);
void			render(t_env *env);
t_double3		raytracer(t_vector ray, t_objects *objects, int depth);
t_double3		reflect(t_double3 incidence, t_double3 normal);
t_double3		refract(t_double3 incidence, t_double3 normal, double ior);
t_double3		fresnel(t_double3 incidence, t_double3 normal, double ior, double *kr);

int				intersect(t_vector ray, t_objects *objects, t_surface *surface);
int				get_nearest_sphere(t_vector ray, t_array *spheres, t_surface *surface);
int				get_nearest_plane(t_vector ray, t_array *planes, t_surface *surface);

void			color_pixel_image(t_color color, int pixel_start, t_image *image);
void			swap(double *t0, double *t1);
double			dot_product(t_double3 vec1, t_double3 vec2);
t_double3		normalize(t_double3 vec);
t_double3		find_point(t_double3 origin, t_double3 dir, double scalar);
t_double3		vec_minus_vec(t_double3 vec1, t_double3 vec2);
t_double3		vec_plus_vec(t_double3 vec1, t_double3 vec2);
t_double3		scale_vec(t_double3 vec, double scalar);
double			max_double(double a, double b);
double			min_double(double a, double b);


void			draw_control(t_env *env);
void			ft_draw_small_arrow(t_env *env);
void			draw_square(t_env *env);
void			ft_draw_left_arrow(t_env *env);
void			ft_draw_right_arrow(t_env *env);
void			draw_value(t_env *env);
void			draw_new_obj_menu(t_env *env);
void			draw_new_obj_add(t_env *env);
int				key_obj_in(int keycode, t_env *env);
char			*search_type_obj(int c);
void			key_add(int keycode, t_env *env);
void			add_num_sphere(t_env *env);
void			add_num_plane(t_env *env);
void			add_num_disk(t_env *env);
void			draw_plane_value(t_env *env);
void			draw_sphere_value(t_env *env);
void			draw_disk_value(t_env *env);
void			init_new_obj(t_env *env);
int				key_new_obj_in(int keycode, t_env *env);

#endif