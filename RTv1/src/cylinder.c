#include "../rtv1.h"

int				intersect_cylinder(t_double3 origin, t_double3 dir, t_cylinder *cylinder, double *distance)
{
	t_double3		pos;
	double			a;
	double			b;
	double			c;
	double 			discr;
	double			t0;
	double			t1;

	pos = vec_minus_vec(origin, cylinder->pos);
	a = sqrt(vec_minus_vec(dir, dot_product(dot_product(dir,
	cylinder->normal), cylinder->normal)));
	b = 2 * (vec_minus_vec(dir, dot_product(pos, 
	dot_product(cylinder->normal, dot_product(cylinder->normal, dir))))
	- vec_minus_vec(pos, dot_product(cylinder->normal,
	dot_product(cylinder->normal, pos))));
	c = sqrt(vec_minus_vec(pos, dot_product(cylinder->normal,
	dot_product(pos, cylinder->normal)))) - sqrt(cylinder->radius);
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else
	{
		t0 = (- b - sqrt(discr)) / (2 * a);
		t1 = (- b + sqrt(discr)) / (2 * a);
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
				return (0);
		}
		*distance = t0;
	}
	return (1);
}