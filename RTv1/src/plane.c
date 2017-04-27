#include "../rtv1.h"

int				intersect_plane(t_vector ray, t_object *plane,
	double *distance)
{
	double		t;

	if (abs_double(ray.dir.z) < 0.00001)
		return (0);
	if ((t = -ray.pos.z / ray.dir.z) < 0)
		return (0);
	*distance = t;
	return (1);
}

void			get_nearest_plane(t_vector ray, t_object *plane,
	t_surface *surface)
{
	double		distance;

	ray = transform_ray(ray, plane);
	if (intersect_plane(ray, plane, &distance))
	{
		surface->object = plane;
		surface->distance = distance;
		surface->normal = (t_double3){0, 0, 1};
	}
}
