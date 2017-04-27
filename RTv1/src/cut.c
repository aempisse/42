#include "../rtv1.h"

int				is_between_cuts(t_double3 point, t_object *object)
{
	if (point.x > object->dcp_min.x && point.x < object->dcp_max.x &&
		point.y > object->dcp_min.y && point.y < object->dcp_max.y &&
		point.z > object->dcp_min.z && point.z < object->dcp_max.z)
		return (1);
	return(0);
}

int				is_inside_object(t_double3 point, t_object *object)
{

}

t_object		*create_cut_plane(double position, char axis)
{
	t_object	*cut_plane;

	cut_plane = new_object(PLANE);
	if (axis = 'x')
	{
		cut_plane->pos.x = position;
		cut_plane->rotation.x = 90;
	}
	else if (axis = 'y')
	{
		cut_plane->pos.y = position;
		cut_plane->rotation.y = 90;
	}
	else
		cut_plane->pos.z = position;
	return (cut_plane);
}

int				get_cut_object(t_vector ray, t_object *object, double *valid, char axis)
{
	t_object	*cut_plane_min;
	t_object	*cut_plane_max;
	t_double2	distance;
	t_vector	ray_plane[2];

	cut_plane_min = create_cut_plane(object->dcp_min.x, axis);  //variable to change
	cut_plane_max = create_cut_plane(object->dcp_max.x, axis);
	ray_plane[0] = transform_ray(ray, cut_plane_min);
	ray_plane[1] = transform_ray(ray, cut_plane_max);
	distance = (t_double2){-1, -1};
	if (intersect_plane(ray_plane[0], cut_plane_min, &(distance.x)) ||
		intersect_plane(ray_plane[1], cut_plane_max, &(distance.y)))
	{

		return(1);
	}
	return (0);
}

int				cut_object(t_vector ray, t_object *object, t_surface *surface, t_double2 *distance)
{
	double		valid;
	t_double3	intersect[2];
	double		distance_x;

	valid = -1;
	intersect[0] = find_point(ray.pos, ray.dir, distance->x);
	intersect[1] = find_point(ray.pos, ray.dir, distance->y);
	if (distance->x > 0 && is_between_cuts(intersect[0]))
		valid = distance->x;
	if (distance->y > 0 && is_between_cuts(intersect[1]))
		valid = distance->x < distance->y ? distance->x : distance->y;
	if (get_cut_object(ray, object, distance_x, 'x'))
	{
		valid = min_positive(distance_x, valid);
	}
	return (valid > 0 ? 1 : 0);
}