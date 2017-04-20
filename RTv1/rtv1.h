#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
// # include <mlx.h>
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

# define WIDTH		1200
# define HEIGHT		900
# define FOV		30
# define DEPTH_MAX	5

	 // Key pour Linux 
# define KEY_ESC	65307

	// Key pour Mac 
// # define KEY_ESC	53

# define PI			3.14159265

# define SPHERE		1
# define PLANE		2
# define CYLINDER	3
# define CONE		4

# define REGULAR_MATRIX	1
# define INVERSE_MATRIX -1

typedef struct		s_double2
{
	double			x;
	double			y;
}					t_double2;

typedef struct		s_double3
{
	double			x;
	double			y;
	double			z;
}					t_double3;

typedef struct		s_vector
{
	t_double3		position;
	t_double3		direction;
}					t_vector;

typedef struct		s_light
{
	t_double3		position;
	t_double3		direction;
	t_double3		color;
	struct s_light	*next;
}					t_light;

typedef struct		s_object
{
	int				type;
	t_double3		position;
	t_double3		rotation;
	double			radius;
	t_double3		color;
	double			reflexion;
	double			transparency;
	double			gloss;
	double			refraction;
	struct s_object	*next;
}					t_object;

typedef struct		s_surface
{
	t_object		*object;
	double			distance;
	t_double3		point;
	t_double3		normal;
	t_double3		simple;
}					t_surface;

typedef struct		s_scene
{
	t_object		*objects;
	t_light			*lights;
	t_vector		camera;
}					t_scene;

typedef struct		s_env
{
	void			*mlx;
	void			*win_scene;
	t_image			*img;
	t_scene			*scene;
	int				render;
}					t_env;

int					loop_hook(t_env *env);
int					key_hook(int keycode, t_env *env);
void				ft_load_file(int fd, t_scene *scene);

t_light				*light_new(void);
void				light_add(t_light **first, t_light *new);
void				print_light(t_light *first);
t_object			*object_new(void);
void				object_add(t_object **first, t_object *new);
void				print_object(t_object *first);

void				render(t_env *env);
t_double3			rotation(t_double3 point, t_double3 angles, int inverse);
t_double3			raytracer(t_vector ray, t_scene *scene, t_object *to_ignore, int depth);
t_surface			*intersect(t_vector ray, t_scene *scene, t_object *to_ignore);

void				color_standard(t_env *env, t_double3 color, int x, int y);


t_double3			reflect(t_double3 incidence, t_double3 normal);
t_double3			refract(t_double3 incidence, t_double3 normal, double ior);
// void			fresnel(t_double3 incidence, t_double3 normal, double ior, double *kr);

void				get_nearest_sphere(t_vector ray, t_object *sphere, t_surface **surface);
void				get_nearest_plane(t_vector ray, t_object *plane, t_surface **surface);
void				get_nearest_cylinder(t_vector ray, t_object *cylinder, t_surface **surface);
void				get_nearest_cone(t_vector ray, t_object *cone, t_surface **surface);

t_vector			transform_ray(t_vector ray, t_object *object);
int					solve_quadratic(double a, double b, double c, double *distance);
void				swap(double *t0, double *t1);
t_double3			find_point(t_double3 origin, t_double3 dir, double scalar);
double				dot_product(t_double3 vec1, t_double3 vec2);
t_double3			normalize(t_double3 vec);
double				length_v(t_double3 vec);
t_double3			scale_v(t_double3 vec, double scalar);
t_double3 			v_scale_v(t_double3 vec1, t_double3 vec2);
t_double3			v_minus_v(t_double3 vec1, t_double3 vec2);
t_double3			v_plus_v(t_double3 vec1, t_double3 vec2);
double				max_double(double a, double b);
double				min_double(double a, double b);
double				abs_double(double n);

#endif