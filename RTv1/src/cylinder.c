#include "../rtv1.h"

static int				intersect_cylinder(t_vector ray, t_object *cylinder, double *distance)
{
	double			a;
	double			b;
	double			c;

	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	b = 2 * (ray.position.x * ray.direction.x + ray.position.y *
		ray.direction.y);
	c = ray.position.x * ray.position.x + ray.position.y * ray.position.y -
		cylinder->radius * cylinder->radius;
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_cylinder(t_vector ray, t_object *cylinder, t_surface **surface)
{
	double			distance;

	ray = transform_ray(ray, cylinder);
	if (intersect_cylinder(ray, cylinder, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.position, ray.direction, distance);
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.position, ray.direction, distance);
		}
	}
}