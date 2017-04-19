#include "../rtv1.h"

t_vector			transform_ray(t_vector ray, t_object *object)
{
	t_vector		new_ray;

	new_ray.position = v_minus_v(ray.position, object->position);
	new_ray.position = rotation(new_ray.position, object->rotation, INVERSE_MATRIX);
	// printf("new_ray.position : (%.2f, %.2f, %.2f)\n", new_ray.position.x, new_ray.position.y, new_ray.position.z);
	new_ray.direction = rotation(ray.direction, object->rotation, INVERSE_MATRIX);
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
	t0 = (- b - sqrt(delta)) / (2 * a);
	t1 = (- b + sqrt(delta)) / (2 * a);
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

t_double3		normalize(t_double3 vec)
{
	t_double3	normalized;
	double		norm;

	norm = 1.0 / length_v(vec);
	normalized.x = vec.x * norm;
	normalized.y = vec.y * norm;
	normalized.z = vec.z * norm;
	return (normalized);
}

double			length_v(t_double3 vec)
{
	double		square;

	if ((square = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)) == 0)
		// return ((t_double3){0, 0, 0});
		ft_error("normal error");
	return (square);
}

t_double3		scale_v(t_double3 vec, double scalar)
{
	t_double3	new_vec;

	new_vec.x = vec.x * scalar;
	new_vec.y = vec.y * scalar;
	new_vec.z = vec.z * scalar;
	return (new_vec);
}

t_double3 		v_scale_v(t_double3 vec1, t_double3 vec2)
{
	t_double3 	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	result.z = vec1.z * vec2.z;
	return (result);
}

t_double3		v_minus_v(t_double3 vec1, t_double3 vec2)
{
	t_double3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_double3		v_plus_v(t_double3 vec1, t_double3 vec2)
{
	t_double3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

double			dot_product(t_double3 vec1, t_double3 vec2)
{
	double		product;

	product = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (product);
}

t_double3		find_point(t_double3 origin, t_double3 dir, double scalar)
{
	t_double3	point;

	point.x = origin.x + dir.x * scalar;
	point.y = origin.y + dir.y * scalar;
	point.z = origin.z + dir.z * scalar;
	return (point);
}

double			max_double(double a, double b)
{
	return ((a > b) ? a : b);
}

double			min_double(double a, double b)
{
	return ((a < b) ? a : b);
}

double			abs_double(double n)
{
	return ((n > 0) ? n : -n);
}