#include "../rtv1.h"

static int				intersect_cone(t_vector ray, t_object *cone, double *distance)
{
	double			angle;
	double			tan_squared;
	double			a;
	double			b;
	double			c;

	ray = transform_ray(ray, cone);
	angle = cone->radius * (M_PI / 180);
	tan_squared = tan(angle) * tan(angle);
	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y - (ray.direction.z * ray.direction.z)
		* tan_squared;
	b = 2 * (ray.position.x * ray.direction.x + ray.position.y * ray.direction.y - ray.direction.x * cone->position.x
		- ray.direction.y * cone->position.y + (ray.direction.z * (cone->position.z - ray.position.z)))
		* tan_squared;
	c = ray.position.x * ray.position.x + ray.position.y * ray.position.y + cone->position.x * cone->position.x
		+ cone->position.y * cone->position.y - 2 * (ray.position.x * cone->position.x + ray.position.y * cone->position.y)
		- (ray.position.z * ray.position.z - 2 * (ray.position.z * cone->position.z) + cone->position.z * cone->position.z)
		* tan_squared;

	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_cone(t_vector ray, t_object *cone, t_surface **surface)
{
	double			distance;

	distance = 0;
	if (intersect_cone(ray, cone, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cone;
			(*surface)->distance = distance;
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cone;
			(*surface)->distance = distance;
		}
	}
}