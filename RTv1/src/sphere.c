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
	t_surface		*tmp;

	ray = transform_ray(ray, sphere);
	if (intersect_sphere(ray, sphere, &distance))
	{
		if (sphere->dcp)
		{
			tmp = cut_object(ray, sphere, &distance);
			if (tmp->object != NULL && (surface->distance == -1 || surface->distance > tmp->distance))
			{
				surface->object = tmp->object;
				surface->distance = tmp->distance;
				surface->normal = tmp->normal;
			}
		}
		else if (surface->distance == -1 || surface->distance > min_positive(distance.x, distance.y))
		{
			surface->object = sphere;
			surface->distance = min_positive(distance.x, distance.y);
			surface->normal = find_point(ray.pos, ray.dir, surface->distance);
		}
	}
}
