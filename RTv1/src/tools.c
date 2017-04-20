#include "../rtv1.h"

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
