#include "../rtv1.h"

static int			intersect_sphere(t_vector ray, t_object *sphere, double *distance)
{
	t_double3	center;
	double		a;
	double		b;
	double		c;

	center = v_minus_v(ray.position, sphere->position);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, center);
	c = dot_product(center, center) - sphere->radius * sphere->radius;
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_sphere(t_vector ray, t_object *sphere, t_surface **surface)
{
	double			distance;

	distance = 0;
	if (intersect_sphere(ray, sphere, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = sphere;
			(*surface)->distance = distance;
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = sphere;
			(*surface)->distance = distance;
		}
	}
}