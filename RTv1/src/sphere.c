#include "../rtv1.h"

static int			intersect_sphere(t_vector ray, t_object *sphere,
	t_double2 *distance)
{
	double		a;
	double		b;
	double		c;

	a = dot_product(ray.dir, ray.dir);
	b = 2 * (ray.pos.x * ray.dir.x + ray.pos.y * ray.dir.y + ray.pos.z * ray.dir.z);
	c = dot_product(ray.pos, ray.pos) - sphere->radius * sphere->radius;
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_sphere(t_vector ray, t_object *sphere,
	t_surface *surface)
{
	t_double2		distance;

	ray = transform_ray(ray, sphere);
	if (intersect_sphere(ray, sphere, &distance))
	{
		if (sphere->dcp)
		{
			if (cut_object(ray, sphere, surface, &distance))
			{

			}
			return ;
		}
		surface->object = sphere;
		surface->distance = min_positive(distance.x, distance.y);
		surface->simple = find_point(ray.pos, ray.dir, surface->distance);
	}
}
