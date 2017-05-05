#include "../rtv1.h"

static int		intersect_cylinder(t_vector ray, t_object *cylinder,
	t_double2 *distance)
{
	double		a;
	double		b;
	double		c;

	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * (ray.pos.x * ray.dir.x + ray.pos.y *
		ray.dir.y);
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y -
		cylinder->radius * cylinder->radius;
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void			get_nearest_cylinder(t_vector ray, t_object *cylinder,
	t_surface *surface, t_scene *scene)
{
	t_double2		distance;
	t_surface		*tmp;
	t_vector		ray_s;

	ray_s = transform_ray(ray, cylinder);
	if (intersect_cylinder(ray_s, cylinder, &distance))
	{
		tmp = cut_object(ray, cylinder, distance, scene);
		if (tmp->object != NULL && (surface->distance == -1 || surface->distance > tmp->distance))
		{
			surface->object = tmp->object;
			surface->distance = tmp->distance;
			surface->normal = tmp->normal;
			// surface->color = tmp->object->color;
			surface->color = get_texture(scene, surface, ray_s);
			free(tmp);
		}
	}
}
