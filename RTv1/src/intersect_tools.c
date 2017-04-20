#include "../rtv1.h"

t_vector		transform_ray(t_vector ray, t_object *object)
{
	t_vector	new_ray;

	new_ray.pos = v_minus_v(ray.pos, object->pos);
	new_ray.pos = rotation(new_ray.pos, object->rotation, INVERSE_MATRIX);
	new_ray.dir = rotation(ray.dir, object->rotation, INVERSE_MATRIX);
	return (new_ray);
}

int				solve_quadratic(double a, double b, double c, double *distance)
{
	double		delta;
	double		t0;
	double		t1;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	t0 = (-b - sqrt(delta)) / (2 * a);
	t1 = (-b + sqrt(delta)) / (2 * a);
	if (t0 > t1)
		swap(&t0, &t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	*distance = t0;
	return (1);
}

void			swap(double *t0, double *t1)
{
	double tmp;

	tmp = *t0;
	*t0 = *t1;
	*t1 = tmp;
}
