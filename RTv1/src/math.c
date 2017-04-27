#include "../rtv1.h"

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
	return ((n > 0.0) ? n : -n);
}

double			min_positive(double a, double b)
{
	double		min_pos;

	if (a > 0)
		min_pos = a;
	if (b > 0 && b < a)
		min_pos = b;
	return (min_pos);
}