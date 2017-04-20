#include "../rtv1.h"

static int				intersect_cone(t_vector ray, t_object *cone, double *distance)
{
	double			angle;
	double			tan_squared;
	double			a;
	double			b;
	double			c;
	t_double3		test_limit;

	angle = cone->radius * (M_PI / 180.0);
	tan_squared = tan(angle) * tan(angle);
	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y -
		(ray.direction.z * ray.direction.z) * angle;
	b = 2 * (ray.position.x * ray.direction.x + ray.position.y *
		ray.direction.y - ray.position.z * ray.direction.z * angle);
	c = ray.position.x * ray.position.x + ray.position.y * ray.position.y -
		ray.position.z * ray.position.z * angle;
	if (solve_quadratic(a, b, c, distance))
	{
		test_limit = find_point(ray.position, ray.direction, *distance);
		if (test_limit.z > 0 && test_limit.z < 3)
			return (1);
	}
	return (0);
}

void				get_nearest_cone(t_vector ray, t_object *cone, t_surface **surface)
{
	double			distance;

	ray = transform_ray(ray, cone);
	if (intersect_cone(ray, cone, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cone;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.position, ray.direction, distance);
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cone;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.position, ray.direction, distance);
		}
	}
}