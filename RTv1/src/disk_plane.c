#include "../rtv1.h"

int 			intersect_plane(t_double3 origin, t_double3 dir, t_plane *plane, double *distance)
{
	double			denom;

	plane->normal = normalize(plane->normal);
	denom = dot_product(dir, plane->normal);
	if (denom > 0.00001)
		*distance = dot_product(vec_minus_vec(origin.pos, plane->pos)
		, plane->normal) / denom;
	else
		return (0);
	return (1);
}