#include "../rtv1.h"

void				get_surface_normal(t_surface *surface, t_double3 ray_dir)
{
	t_double3		normal;

	if (surface->object->type == SPHERE)
		surface->normal = rotation(surface->simple,
			surface->object->rotation, REGULAR_MATRIX);
	if (surface->object->type == PLANE)
		surface->normal = rotation((t_double3){0, 0, 1},
			surface->object->rotation, REGULAR_MATRIX);
	// if (surface->object->type == CYLINDER)
	// 	surface->normal = rotation((t_double3){surface->simple.x,
	// 		surface->simple.y, 0}, surface->object->rotation, REGULAR_MATRIX);
	// if (surface->object->type == CONE)
	// 	surface->normal = rotation((t_double3){surface->simple.x,
	// 		surface->simple.y, -1 * surface->simple.z * surface->object->radius
	// 		* (M_PI / 180.0)}, surface->object->rotation, REGULAR_MATRIX);
	surface->normal = normalize(surface->normal);
	if (dot_product(surface->normal, ray_dir) > 0)
		surface->normal = scale_v(surface->normal, -1);
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
			get_nearest_sphere(ray, tmp, surface);
		if (tmp != to_ignore && tmp->type == PLANE)
			get_nearest_plane(ray, tmp, surface);
		// if (tmp != to_ignore && tmp->type == CYLINDER)
		// 	get_nearest_cylinder(ray, tmp, surface);
		// if (tmp != to_ignore && tmp->type == CONE)
		// 	get_nearest_cone(ray, tmp, surface);
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
