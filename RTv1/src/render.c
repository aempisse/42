#include "../rtv1.h"

t_double3		pixel_ray_init(t_double3 camera_dir, int x, int y)
{
	t_double3	pixel_ray;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	pixel_ray.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
	pixel_ray.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_ray.z = -1;
	pixel_ray = normalize(pixel_ray);
	pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
	return (pixel_ray);
}

void			render(t_env *env)
{
	int			x;
	int			y;
	t_double3	pixel_ray;
	t_double3	color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_ray = pixel_ray_init(env->scene->camera.dir, x, y);
			color = raytracer((t_vector){env->scene->camera.pos, pixel_ray},
				env->scene, NULL, 0);
			color_standard(env, color, x, y);
		}
	}
}
