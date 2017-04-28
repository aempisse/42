#include "../rtv1.h"

int				is_between_cuts(t_double3 point, t_object *object)
{
	if (point.x > object->dcp_min.x && point.x < object->dcp_max.x &&
		point.y > object->dcp_min.y && point.y < object->dcp_max.y &&
		point.z > object->dcp_min.z && point.z < object->dcp_max.z)
		return (1);
	return(0);
}

int				is_inside_sphere(t_double3 point, t_object *object)
{
	if (length_v(point) < object->radius)
		return (1);
	return (0);
}

t_object		*create_cut_plane(double position, char axis)
{
	t_object	*cut_plane;

	cut_plane = object_new(PLANE);
	if (axis == 'x')
	{
		cut_plane->pos.x = position;
		cut_plane->rotation.y = 90;
	}
	// else if (axis == 'y')
	// {
	// 	cut_plane->pos.y = position;
	// 	cut_plane->rotation.y = 90;
	// }
	// else
	// 	cut_plane->pos.z = position;
	return (cut_plane);
}

int				get_cut_object(t_vector ray, t_object *object, double *valid, char axis)
{
	t_object	*cut_plane_min;
	t_object	*cut_plane_max;
	t_vector	ray_min;
	t_vector	ray_max;
	t_double2	distance;

	cut_plane_min = create_cut_plane(object->dcp_min.x, axis);  //variable to change
	cut_plane_max = create_cut_plane(object->dcp_max.x, axis);
	ray_min = transform_ray(ray, cut_plane_min);
	ray_max = transform_ray(ray, cut_plane_max);
	distance = (t_double2){-1, -1};
	if (intersect_plane(ray_min, cut_plane_min, &(distance.x)) ||
		intersect_plane(ray_max, cut_plane_max, &(distance.y)))
	{
		if (distance.x > 0 && is_inside_sphere(find_point(ray.pos, ray.dir, distance.x), object))
			*valid = distance.x;
		if (distance.y > 0 && is_inside_sphere(find_point(ray.pos, ray.dir, distance.y), object))
			*valid = min_positive(distance.y, *valid);
	}
	free(cut_plane_min);
	free(cut_plane_max);
	return (*valid > 0 ? 1 : 0);
}

t_surface		*cut_object(t_vector ray_s, t_vector ray_r, t_object *object, t_double2 *distance)
{
	double		distance_cut;
	t_surface	*tmp;

	tmp = (t_surface*)malloc(sizeof(t_surface));
	tmp->distance = -1;
	if (distance->x > 0 && is_between_cuts(find_point(ray_s.pos, ray_s.dir, distance->x), object))
	{
		tmp->distance = distance->x;
		tmp->normal = find_point(ray_s.pos, ray_s.dir, tmp->distance);	//sphere
	}
	if (distance->y > 0 && is_between_cuts(find_point(ray_s.pos, ray_s.dir, distance->y), object))
	{
		tmp->distance = min_positive(distance->y, tmp->distance);
		tmp->normal = find_point(ray_s.pos, ray_s.dir, tmp->distance);	//sphere
	}
	// distance_cut = -1;
	// if (get_cut_object(ray_s, object, &distance_cut, 'x'))		// X axis cut
	// {
	// 	if (min_positive(distance_cut, tmp->distance) == distance_cut)
	// 	{
	// 		tmp->distance = distance_cut;
	// 		tmp->normal = (t_double3){1, 0, 0};			// normal for an X axis cut
	// 	}
	// }
	tmp->object = (tmp->distance > 0 ? object : NULL);
	return (tmp);
}