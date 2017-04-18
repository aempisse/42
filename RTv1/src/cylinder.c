#include "../rtv1.h"

static int				intersect_cylinder(t_vector ray, t_object *cylinder, double *distance)
{
	double			a;
	double			b;
	double			c;

	ray = transform_ray(ray, cylinder);
	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	b = 2 * (ray.position.x * ray.direction.x + ray.position.y * ray.direction.y
		- ray.direction.x * cylinder->position.x - ray.direction.y * cylinder->position.y);
	c = ray.position.x * ray.position.x + ray.position.y * ray.position.y + cylinder->position.x *
		cylinder->position.x + cylinder->position.y * cylinder->position.y - cylinder->radius * cylinder->radius - 2 *
		(ray.position.x * cylinder->position.x + ray.position.y * cylinder->position.y);
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_cylinder(t_vector ray, t_object *cylinder, t_surface **surface)
{
	double			distance;

	distance = 0;
	if (intersect_cylinder(ray, cylinder, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cylinder;
			(*surface)->distance = distance;
		}
	}
}