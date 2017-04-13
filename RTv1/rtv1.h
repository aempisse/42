#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
// # include <mlx.h>
# include "minilibx/mlx.h"
# include <math.h>
# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 800
# define FOV 30
# define DEPTH_MAX 5

	 // Key pour Linux 
# define KEY_ESC 65307

	// Key pour Mac 
// # define KEY_ESC 53

# define PI 3.14159265

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4

# define DIFFUSE_GLOSSY 0
# define REFLECTION 1
# define REFLECTION_AND_REFRACTION 2

# define BIAS 0.00001

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
	void			*object;
	double			distance;
	t_double3		p_hit;
	t_double3		n_hit;
	t_double3		color;
	double			ior;
	int				material;
}					t_surface;

typedef struct		s_env
{
	void			*mlx;
	void			*win_scene;
	t_image			*img;
	t_object		**objects;
	t_light			**lights;
	t_vector		camera;
	int				render;
}					t_env;

int				loop_hook(t_env *env);
int				key_hook(int keycode, t_env *env);
void			ft_load_file(int fd, t_env *env);

t_light			*light_new(void);
void			light_add(t_light **first, t_light *new);
t_object		*object_new(void);
void			object_add(t_object **first, t_object *new);

// void			render(t_env *env);
// t_double3		raytracer(t_vector ray, t_objects *objects, void *to_ignore, int depth);
// t_double3		reflect(t_double3 incidence, t_double3 normal);
// t_double3		refract(t_double3 incidence, t_double3 normal, double ior);
// void			fresnel(t_double3 incidence, t_double3 normal, double ior, double *kr);

// t_surface		*intersect(t_vector ray, t_objects *objects, void *to_ignore);
// void			get_nearest_sphere(t_vector ray, t_array *spheres, t_surface **surface, void *to_ignore);
// void			get_nearest_plane(t_vector ray, t_array *planes, t_surface **surface, void *to_ignore);
// void			get_nearest_cylinder(t_vector ray, t_array *cylinder, t_surface **surface, void *to_ignore);
// void			get_nearest_cone(t_vector ray, t_array *cones, t_surface **surface, void *to_ignore);

// void			color_pixel_image(t_color color, int pixel_start, t_image *image);
// void			swap(double *t0, double *t1);
// double			dot_product(t_double3 vec1, t_double3 vec2);
// t_double3		normalize(t_double3 vec);
// t_double3		find_point(t_double3 origin, t_double3 dir, double scalar);
// t_double3		vec_minus_vec(t_double3 vec1, t_double3 vec2);
// t_double3		vec_plus_vec(t_double3 vec1, t_double3 vec2);
// t_double3		scale_vec(t_double3 vec, double scalar);
// t_double3 		vec_scale_vec(t_double3 vec1, t_double3 vec2);
// double			max_double(double a, double b);
// double			min_double(double a, double b);
// double			abs_double(double n);

// t_double3		rotation_x(t_double3 point, double angle);
// t_double3		rotation_y(t_double3 point, double angle);
// t_double3		rotation_z(t_double3 point, double angle);

#endif