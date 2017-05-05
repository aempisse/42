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
	t_surface *surface, t_scene *scene)
{
	double		distance;
	t_surface	*tmp;
	t_vector	ray_s;

	ray_s = transform_ray(ray, plane);
	if (intersect_plane(ray_s, plane, &distance))
	{
		if (plane->radius > 0.00001 && length_v(find_point(ray_s.pos, ray_s.dir, distance)) > plane->radius)
				return;
		tmp = cut_object(ray, plane, (t_double2){distance, -1}, scene);
		if (tmp->object != NULL && (surface->distance == -1 || surface->distance > tmp->distance))
		{
			surface->object = tmp->object;
			surface->distance = tmp->distance;
			surface->normal = tmp->normal;
			surface->color = tmp->object->color;
			free(tmp);
		}
	}
}
