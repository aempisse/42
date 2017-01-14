#ifndef RTV1_H
# define RTV1_H

# include "libft/libft.h"
//# include <mlx.h>
# include "minilibx/mlx.h"
# include <math.h>

# define WIDTH 512
# define HEIGHT 512
# define FOV 51.52

# define KEY_ESC 65307

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

typedef struct	s_env
{
	void		*mlx;
	void		*win_scene;
	t_image		*img;
	t_array		*sphere;
	t_array		*plane;
	t_camera	camera;
	double		fov;
	int			render;
}				t_env;

void			ft_load_file(int fd, t_env *env);
void			render(t_env *env);
void			raytracer(t_env *en, int x, int y);
int				intersect(t_env *env, t_double3 dir, t_sphere *sphere);
double			dot_product(t_double3 vec1, t_double3 vec2);
t_double3		normalize(t_double3 vec);

#endif