#include "../rtv1.h"

static int			intersect_plane(t_vector ray, t_object *plane,
	double *distance)
{
	double			t;
	t_double3		cut;

	ray = transform_ray(ray, plane);
	if (abs_double(ray.dir.z) < 0.00001)
		return (0);
	if ((t = -ray.pos.z / ray.dir.z) < 0)
		return (0);
	*distance = t;
	cut = find_point(ray.pos, ray.dir, *distance);
	if (cut.x > plane->dcp_max.x || cut.x < plane->dcp_min.x ||
		cut.y > plane->dcp_max.y || cut.y < plane->dcp_min.y)
		return (0);
	return (1);
}

void				get_nearest_plane(t_vector ray, t_object *plane,
	t_surface **surface)
{
	double			distance;

	distance = 0;
	if (intersect_plane(ray, plane, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = plane;
			(*surface)->distance = distance;
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = plane;
			(*surface)->distance = distance;
		}
	}
}
