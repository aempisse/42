#include "../rtv1.h"

void			ft_put_image(t_image *img, int pos, t_color color)
{
	int			to;

	to = pos + img->opp;
	while (pos < to)
	{
		img->data[pos] = color.b.b;
		color.u >>= 8;
		pos++;
	}
}

t_double3		normalize(t_double3 vec)
{
	t_double3	normalized;
	double		square;
	double		norm;

	if ((square = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)) == 0)
		return ((t_double3){0, 0, 0});
	norm = 1 / square;
	normalized.x = vec.x * norm;
	normalized.y = vec.y * norm;
	normalized.z = vec.z * norm;
	return (normalized);
}

double			dot_product(t_double3 vec1, t_double3 vec2)
{
	double		product;

	product = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (product);
}

int				intersect(t_env *env, t_double3 dir, t_sphere *sphere)
{
	t_double3	center;
	double		a;
	double		b;
	double		c;
	double		discr;

	center.x = env->camera.pos.x - sphere->pos.x;
	center.y = env->camera.pos.y - sphere->pos.y;
	center.z = env->camera.pos.z - sphere->pos.z;
	a = dot_product(dir, dir);
	b = 2 * dot_product(dir, center);
	c = dot_product(center, center) - sphere->radius * sphere->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	return (1);
}

void			raytracer(t_env *env, int x, int y)
{
	double		aspect_ratio;
	double		scale;
	t_double3	pixel_camera;
	t_sphere	*tmp;
	t_color		color;
	int			i;

	aspect_ratio = WIDTH / (double)HEIGHT;
	scale = tan((env->fov * 0.5) * PI / 180.0);
	pixel_camera.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
	pixel_camera.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_camera.z = -1;
	pixel_camera = normalize(pixel_camera);
	i = -1;
	color.u = 0x00000000;
	while (++i < env->sphere->length)
	{
		tmp = AG(t_sphere*, env->sphere, i);
		if (intersect(env, pixel_camera, tmp))
			color.u = 0x00FFFFFF;
	}
	ft_put_image(env->img, (WIDTH * y + x) * env->img->opp, color);
}

void			render(t_env *env)
{
	int			x;
	int			y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			raytracer(env, x, y);
	}
}