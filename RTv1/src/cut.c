#include "../rtv1.h"

int				is_between_cuts(t_vector ray_s, double distance, t_object *object)
{
	t_double3	point;

	point = find_point(ray_s.pos, ray_s.dir, distance);
	if (object->dcp == 0)
		return (1);
	if (point.x < object->dcp_x.x || point.x > object->dcp_x.y ||
		point.y < object->dcp_y.x || point.y > object->dcp_y.y ||
		point.z < object->dcp_z.x || point.z > object->dcp_z.y)
		return (0);
	return(1);
}

int				is_in_negative(t_scene *scene, t_vector ray_r, double distance)
{
	t_negobj	*negative;
	t_double3	point;

	point = find_point(ray_r.pos, ray_r.dir, distance);
	negative = scene->negobj;
	while (negative)
	{
		if (length_v(v_minus_v(point, negative->pos)) < negative->radius)
			return (1);
		negative = negative->next;
	}
	return (0);
}

t_surface		*cut_object(t_vector ray_r, t_object *object, t_double2 distance, t_scene *scene)
{
	double		distance_cut;
	t_surface	*tmp;
	t_vector	ray_s;

	ray_s = transform_ray(ray_r, object);
	tmp = (t_surface*)malloc(sizeof(t_surface));
	tmp->distance = -1;
	if (distance.x > 0 && is_between_cuts(ray_s, distance.x, object) && !is_in_negative(scene, ray_r, distance.x))
	{
		tmp->distance = distance.x;
		tmp->normal = get_normal(object, find_point(ray_s.pos, ray_s.dir, tmp->distance));
	}
	if (distance.y > 0 && is_between_cuts(ray_s, distance.y, object) && !is_in_negative(scene, ray_r, distance.y))
	{
		tmp->distance = min_positive(distance.y, tmp->distance);
		tmp->normal = get_normal(object, find_point(ray_s.pos, ray_s.dir, tmp->distance));
	}
	tmp->object = (tmp->distance > 0 ? object : NULL);
	return (tmp);
}
