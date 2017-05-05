#include "../rtv1.h"

t_double3			get_normal(t_object *object, t_double3 point)
{
	t_double3		normal;

	normal = (t_double3){0, 0, 1};
	if (object->type == SPHERE)
		normal = point;
	if (object->type == CYLINDER)
		normal = (t_double3){point.x, point.y, 0};
	if (object->type == CONE)
		normal = (t_double3){point.x, point.y, -1 * point.z * object->radius * (M_PI / 180.0)};
	return (normalize(normal));
}

t_surface			*intersect(t_vector ray, t_scene *scene,
	t_object *to_ignore)
{
	t_surface		*surface;
	t_object		*tmp;

	if ((surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
		ft_error("Error : malloc() failed.\n");
	surface->object = NULL;
	surface->distance = -1;
	tmp = scene->object;
	while (tmp)
	{
		if (tmp != to_ignore && tmp->type == SPHERE)
			get_nearest_sphere(ray, tmp, surface, scene);
		if (tmp != to_ignore && tmp->type == PLANE)
			get_nearest_plane(ray, tmp, surface, scene);
		if (tmp != to_ignore && tmp->type == CYLINDER)
			get_nearest_cylinder(ray, tmp, surface, scene);
		if (tmp != to_ignore && tmp->type == CONE)
			get_nearest_cone(ray, tmp, surface, scene);
		tmp = tmp->next;
	}
	if (surface->object != NULL)
	{
		surface->point = find_point(ray.pos, ray.dir, surface->distance);
		surface->normal = rotation(surface->normal, surface->object->rotation, REGULAR_MATRIX);
		surface->normal = normalize(surface->normal);
		if (dot_product(surface->normal, ray.dir) > 0)
			surface->normal = scale_v(surface->normal, -1);
	}
	return (surface);
}
