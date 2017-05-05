#include "../rtv1.h"

t_double3		normalize(t_double3 vec)
{
	t_double3	normalized;
	double		norm;
	double		length;

	length = length_v(vec);
	if (abs_double(length) < 0.00001)
		return ((t_double3){0, 0, 0});
	norm = 1.0 / length;
	normalized.x = vec.x * norm;
	normalized.y = vec.y * norm;
	normalized.z = vec.z * norm;
	return (normalized);
}

double			dot_product(t_double3 vec1, t_double3 vec2)
{
	double		dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

t_double3		cross_product(t_double3 vec1, t_double3 vec2)
{
	t_double3	cross;

	cross.x = vec1.y * vec2.z - vec1.z * vec2.y;
	cross.y = vec1.z * vec2.x - vec1.x * vec2.z;
	cross.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (cross);
}

t_double3		find_point(t_double3 origin, t_double3 dir, double scalar)
{
	t_double3	point;

	point.x = origin.x + dir.x * scalar;
	point.y = origin.y + dir.y * scalar;
	point.z = origin.z + dir.z * scalar;
	return (point);
}
