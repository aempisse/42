#include "../rtv1.h"

double			length_v(t_double3 vec)
{
	double		square;

	if ((square = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)) == 0)
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

t_double3		v_scale_v(t_double3 vec1, t_double3 vec2)
{
	t_double3	result;

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
