#include "../rtv1.h"

void				get_surface_normal(t_surface *surface)
{
	t_double3		normal;

	if (surface->object->type == SPHERE)
		surface->normal = v_minus_v(surface->point, surface->object->position);
	if (surface->object->type == PLANE)
		surface->normal = rotation((t_double3){0, 0, -1}, surface->object->rotation, REGULAR_MATRIX);
	if (surface->object->type == CYLINDER)
		surface->normal = rotation((t_double3){surface->point.x, surface->point.y, 0},
			surface->object->rotation, REGULAR_MATRIX);
	if (surface->object->type == CONE)
		surface->normal = rotation((t_double3){surface->point.x, surface->point.y,
			surface->point.z * (-surface->object->radius)}, surface->object->rotation, REGULAR_MATRIX);
	normalize(surface->normal);
}

t_surface			*intersect(t_vector ray, t_scene *scene, t_object *to_ignore)
{
	t_surface		*surface;
	t_object		*tmp;

	surface = NULL;
	tmp = scene->objects;
	while (tmp)
	{
		if (tmp != to_ignore)
		{
			if (tmp->type == SPHERE)
				get_nearest_sphere(ray, tmp, &surface);
			if (tmp->type == PLANE)
				get_nearest_plane(ray, tmp, &surface);
			if (tmp->type == CYLINDER)
				get_nearest_cylinder(ray, tmp, &surface);
			if (tmp->type == CONE)
				get_nearest_cone(ray, tmp, &surface);
		}
		tmp = tmp->next;
	}
	if (surface != NULL)
	{
		surface->point = find_point(ray.position, ray.direction, surface->distance);
		get_surface_normal(surface);
	}
	return (surface);
}

t_double3			raytracer(t_vector ray, t_scene *scene, t_object *to_ignore, int depth)
{
	t_surface		*surface;
	t_double3		color_hit;
	t_light			*light;
	t_vector		light_ray;
	t_surface		*light_intersect;
	int				light_nb;
	double			dot_light;

	if (depth > DEPTH_MAX)
		return ((t_double3){0.1, 0.1, 0.1});
	surface = intersect(ray, scene, to_ignore);
	if (surface == NULL)
		return ((t_double3){0.1, 0.1, 0.1});
	else
	{
		// color_hit = surface->object->color;
		color_hit = (t_double3){0, 0, 0};
		light = scene->lights;
		light_nb = 0;
		while (light)
		{
			light_ray.position = surface->point;
			light_ray.direction = normalize(v_minus_v(light->position, surface->point));
			dot_light = dot_product(light_ray.direction, surface->normal);
			if (surface->object->type == PLANE)
				dot_light = abs_double(dot_light);
			light_intersect = intersect(light_ray, scene, surface->object);
			if (light_intersect != NULL && (length_v(v_minus_v(light->position, surface->point)) <
					light_intersect->distance))
			{
				color_hit = v_plus_v(color_hit, scale_v(surface->object->color, dot_light));
			}
			light_nb++;
			light = light->next;
		}
		color_hit = scale_v(color_hit, (1 / (double)light_nb));
		free(surface);
		return (color_hit);
	}
}

void			render(t_env *env)
{
	int			x;
	int			y;
	t_double3	pixel_camera;
	double		aspect_ratio;
	double		scale;
	t_double3	color;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_camera.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
			pixel_camera.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
			pixel_camera.z = -1;
			pixel_camera = normalize(pixel_camera);
			// pixel_camera = rotation(pixel_camera, env->scene->camera.direction, REGULAR_MATRIX);
			color = raytracer((t_vector){env->scene->camera.position, pixel_camera}, env->scene, NULL, 0);
			color_standard(env, color, x, y);
		}
	}
}
