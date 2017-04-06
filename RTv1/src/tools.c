#include "../rtv1.h"

void			color_pixel_image(t_color color, int pixel_start, t_image *image)
{
	int			pixel_end;

	pixel_end = pixel_start + image->opp;
	while (pixel_start < pixel_end)
	{
		image->data[pixel_start] = color.b.b;
		color.u >>= 8;
		pixel_start++;
	}
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
	double		square;
	double		norm;

	if ((square = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)) == 0)
		// return ((t_double3){0, 0, 0});
		ft_error("normal error");
	norm = 1.0 / square;
	normalized.x = vec.x * norm;
	normalized.y = vec.y * norm;
	normalized.z = vec.z * norm;
	return (normalized);
}

t_double3 		vec_scale_vec(t_double3 vec1, t_double3 vec2)
{
	t_double3 	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	result.z = vec1.z * vec2.z;
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

t_double3		scale_vec(t_double3 vec, double scalar)
{
	t_double3	new_vec;

	new_vec.x = vec.x * scalar;
	new_vec.y = vec.y * scalar;
	new_vec.z = vec.z * scalar;
	return (new_vec);
}

t_double3		vec_minus_vec(t_double3 vec1, t_double3 vec2)
{
	t_double3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_double3		vec_plus_vec(t_double3 vec1, t_double3 vec2)
{
	t_double3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
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