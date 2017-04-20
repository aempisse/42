#include "../rtv1.h"

static int		intersect_cylinder(t_vector ray, t_object *cylinder,
	double *distance)
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
	t_surface **surface)
{
	double		distance;

	ray = transform_ray(ray, cylinder);
	if (intersect_cylinder(ray, cylinder, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.pos, ray.dir, distance);
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.pos, ray.dir, distance);
		}
	}
}
