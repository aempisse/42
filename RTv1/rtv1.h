#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
# include <mlx.h>
// # include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 800
# define FOV 30
# define DEPTH_MAX 5

	 // Key pour Linux 
// # define KEY_ESC 65307

	// Key pour Mac 
# define KEY_ESC 53

# define PI 3.14159265

# define DIFFUSE_GLOSSY 0
# define REFLECTION 1
# define REFLECTION_AND_REFRACTION 2

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3
# define SPOTLIGHT 4

# define RED "ff0000"
# define BLUE "0000ff"
# define GREEN "00ff00"
# define LIGHT_BLUE "ADD8E6"
# define LIGHT_GREEN "90ee90"
# define ORANGE "ffa500"
# define PINK "ffc0cb"
# define PURPLE "800080"
# define DARK_GREEN "006400"
# define DARK_BLUE "00008b"
# define DARK_RED "8b0000"

# define BIAS 0.00001

# define REGULAR_MATRIX	1
# define INVERSE_MATRIX -1

typedef struct			s_double2
{
	double				x;
	double				y;
}						t_double2;

typedef struct			s_double3
{
	double				x;
	double				y;
	double				z;
}						t_double3;

typedef struct			s_vector
{
	t_double3			pos;
	t_double3			dir;
}						t_vector;

typedef struct			s_light
{
	t_double3			pos;
	t_double3			dir;
	t_double3			color;
	int					type;
	struct s_light		*next;
}						t_light;

typedef struct			s_object
{
	int					type;
	t_double3			pos;
	t_double3			rotation;
	double				radius;
	t_double3			color;
	double				gloss;
	double				refraction;
	double				reflex;
	double				transparency;
	t_double3			dcp_min;
	t_double3			dcp_max;
	struct	s_object	*next;
}						t_object;

typedef struct			s_surface
{
	t_object			*object;
	double				distance;
	t_double3			point;
	t_double3			normal;
	t_double3			simple;
}						t_surface;

typedef struct			s_scene
{
	t_object			*object;
	t_light				*light;
	t_vector			camera;
}						t_scene;

typedef struct			s_pars
{
	int					balise;
	int					nbr_lign;
	int					i_sphere;
	int					i_plane;
	int					i_cylinder;
	int					i_cone;
	int					i_light;
	int					error;
	char				**error_mess;
}						t_pars;

typedef struct			s_env
{
	void				*mlx;
	void				*win_scene;
	t_image				*img;
	t_scene				*scene;
	int					nbr_obj;
	int					render;
}						t_env;

int						loop_hook(t_env *env);
int						key_hook(int keycode, t_env *env);

t_double3				pick_values(t_buff line, int nbr);
void					check_pars_nbr_value(t_buff line, int nbr);
void					empty_lign(t_buff line);

void					add_light_value(t_env *env, t_double3 *values, int i);
void					add_double_param(t_buff line, char *type, t_object **object);
void					add_value(t_env *env, t_double3 *values, int i);

void					check_object_balise(t_env *env, t_buff line, t_pars *pars);
void					check_files(int fd, t_env *env);
void					check_sphere_obj(t_env *env, t_buff line, int i);
void					check_cylinder_obj(t_env *env, t_buff line, int i);
void					check_cone_obj(t_env *env, t_buff line, int i);
void					check_light_obj(t_env *env, t_buff line, int i);
void					check_camera_obj(t_env *env, t_buff line, int i);
void					check_object_name(t_env *env, char *name, t_pars *pars);
void					check_color_obj(t_object **object, char *value);
void					check_color_light(t_light **light, char *value);
void					check_plane_obj(t_env *env, t_buff line, int i);
void					print_object(t_object **first, t_light **first_l);
void					pars_camera_line(t_env *env, t_buff line, int i);
void					pars_light_line(t_env *env, t_buff line, int i);
void					test_decoup_balise(char *line, int i);
void					pars_object_line(t_env *env, t_buff line, int i);


void					init_light_obj(t_env *env, t_pars *pars, int obj, t_light **light);
void					init_object(t_env *env, t_pars *pars, int obj, t_object **object);
void					object_add(t_object **first, t_object *new);
t_object				*object_new(int type);
void					light_add(t_light **first, t_light *new);
t_light					*light_new(int type);


void					swap(double *t0, double *t1);
double					dot_product(t_double3 vec1, t_double3 vec2);
t_double3				normalize(t_double3 vec);
t_double3				find_point(t_double3 origin, t_double3 dir, double scalar);
t_double3				vec_minus_vec(t_double3 vec1, t_double3 vec2);
t_double3				vec_plus_vec(t_double3 vec1, t_double3 vec2);
t_double3				scale_vec(t_double3 vec, double scalar);
t_double3				v_minus_v(t_double3 vec1, t_double3 vec2);
t_double3				rotation(t_double3 point, t_double3 angles, int inverse);
t_double3				scale_v(t_double3 vec, double scalar);
t_double3 				v_scale_v(t_double3 vec1, t_double3 vec2);
t_double3 				vec_scale_vec(t_double3 vec1, t_double3 vec2);
t_double3				v_plus_v(t_double3 vec1, t_double3 vec2);
t_vector				transform_ray(t_vector ray, t_object *object);
double					length_v(t_double3 vec);
double					max_double(double a, double b);
double					min_double(double a, double b);
double					abs_double(double n);
int						solve_quadratic(double a, double b, double c, double *distance);

t_double3				rotation(t_double3 point, t_double3 angles, int inverse);

t_double3				color_reflected(t_vector ray, t_scene *scene, t_surface *surface, int depth);
t_double3				color_refracted(t_vector ray, t_scene *scene,t_surface *surface, int depth);
t_double3				raytracer(t_vector ray, t_scene *scene, t_object *to_ignore, int depth);
t_surface				*intersect(t_vector ray, t_scene *scene, t_object *to_ignore);
void					render(t_env *env);
void					color_standard(t_env *env, t_double3 color, int x, int y);
void					get_surface_normal(t_surface *surface);

void					get_nearest_sphere(t_vector ray, t_object *sphere, t_surface **surface);
void					get_nearest_plane(t_vector ray, t_object *plane, t_surface **surface);
void					get_nearest_cylinder(t_vector ray, t_object *cylinder, t_surface **surface);
void					get_nearest_cone(t_vector ray, t_object *cone, t_surface **surface);

#endif

/* 
typage camera : fov;

object limite :


*/