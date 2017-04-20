#include "../rtv1.h"

t_surface			*is_in_light(t_surface *surface, t_scene *scene,
	t_light *light, double *dot_light)
{
	t_vector		light_ray;
	t_double3		light_distance;
	t_surface		*light_intersect;

	light_ray.pos = surface->point;
	light_distance = v_minus_v(light->pos, surface->point);
	light_ray.dir = normalize(light_distance);
	*dot_light = dot_product(light_ray.dir, surface->normal);
	if (surface->object->type == PLANE)
		*dot_light = abs_double(*dot_light);
	*dot_light = max_double(0, *dot_light);
	light_intersect = intersect(light_ray, scene, surface->object);
	light_intersect->distance -= length_v(light_distance);
	return (light_intersect);
}

t_double3			color_diffused(t_scene *scene, t_surface *surface)
{
	t_double3		color_hit;
	t_light			*light;
	int				light_nb;
	double			dot_light;
	t_surface		*light_intersect;

	color_hit = (t_double3){0, 0, 0};
	light = scene->light;
	light_nb = 0;
	while (light)
	{
		light_intersect = is_in_light(surface, scene, light, &dot_light);
		if (light_intersect != NULL && light_intersect->distance > 0)
			color_hit = v_plus_v(color_hit, v_plus_v(scale_v(
				scale_v(surface->object->color, dot_light), 1 -
				surface->object->gloss), scale_v(scale_v(light->color,
				dot_light), surface->object->gloss)));
		light_nb++;
		light = light->next;
	}
	if (light_nb != 0)
		color_hit = scale_v(color_hit, (1.0 / (double)light_nb));
	return (color_hit);
}

t_double3			raytracer(t_vector ray, t_scene *scene,
	t_object *to_ignore, int depth)
{
	t_surface		*surface;
	t_double3		color_hit;

	if (depth == DEPTH_MAX)
		return ((t_double3){0, 0, 0});
	surface = intersect(ray, scene, to_ignore);
	if (surface == NULL)
		return ((t_double3){0, 0, 0});
	else
	{
		color_hit = (t_double3){0, 0, 0};
		color_hit = color_diffused(scene, surface);
		if (surface->object->reflex > 0.01)
			color_hit = v_plus_v(scale_v(color_hit, 1 -
				surface->object->reflex), scale_v(color_reflected(ray, scene,
				surface, depth), surface->object->reflex));
		if (surface->object->transparency > 0.01)
			color_hit = v_plus_v(scale_v(color_hit, 1 -
				surface->object->transparency), scale_v(color_refracted(ray,
				scene, surface, depth), surface->object->transparency));
		free(surface);
		return (color_hit);
	}
}
