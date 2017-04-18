#include "../rtv1.h"

void				get_surface_normal(t_surface *surface)
{
	t_double3		normal;

	if (surface->object->type == SPHERE)
		surface->normal = v_minus_v(surface->point, surface->object->position);
	if (surface->object->type == PLANE)
		surface->normal = rotation((t_double3){0, 0, -1}, surface->object->rotation);
	if (surface->object->type == CYLINDER)
		surface->normal = rotation((t_double3){surface->point.x, surface->point.y, 0},
			surface->object->rotation);
	if (surface->object->type == CYLINDER)
		surface->normal = rotation((t_double3){surface->point.x, surface->point.y,
			surface->point.z * (- surface->object->radius)}, surface->object->rotation);
	normalize(surface->normal);
}

t_surface			*intersect(t_vector ray, t_scene *scene, void *to_ignore)
{
	t_surface		*surface;
	t_object		*tmp;

	surface = NULL;
	tmp = scene->objects;
	while (tmp)
	{
		if (tmp->type == SPHERE)
			get_nearest_sphere(ray, tmp, &surface);
		if (tmp->type == PLANE)
			get_nearest_plane(ray, tmp, &surface);
		if (tmp->type == CYLINDER)
			get_nearest_cylinder(ray, tmp, &surface);
		if (tmp->type == CONE)
			get_nearest_cone(ray, tmp, &surface);
		tmp = tmp->next;
	}
	if (surface != NULL)
	{
		surface->point = find_point(ray.position, ray.direction, surface->distance);
		get_surface_normal(surface);
	}
	return (surface);
}

// int					is_exposed_to_light(t_surface *surface, t_light *light, t_objects *objects)
// {
// 	t_vector		*light_ray;
// 	double			distance_to_light;
// 	t_surface		*tmp;

// 	light_ray->pos = surface->p_hit;
// 	light_ray->dir = vec_minus_vec(light->pos, surface->p_hit);
// 	distance_to_light = sqrt(light_ray->dir.x * light_ray->dir.x +
// 		light_ray->dir.y * light_ray->dir.y + light_ray->dir.z * light_ray->dir.z);
// 	light_ray->dir = normalize(light_ray->dir);
// 	tmp = intersect(light_ray, objects, surface->object);
// 	if (tmp == NULL)
// 		return (1);
// 	else if (tmp->distance <= distance_to_light)
// 		return (0);
// 	return (1);
// }

// t_double3			phong_illumitation_model(t_vector ray, t_surface surface, t_objects *objects)
// {
// 	t_double3		color_hit;
// 	int				i;
// 	t_light			*light;
// 	t_double3		light_dir;
// 	double			lambert;

// 	color_hit = (t_double3){0, 0, 0};
// 	i = -1;
// 	while (++i < objects->lights->length)
// 	{
// 		light = AG(t_light*, objects->lights, i);
// 		if (is_exposed_to_light(surface, light, objects));
// 		{
// 			light_dir = normalize(vec_minus_vec(light->pos, surface->p_hit));
// 			if (lambert = dot_product(surface->normal, light_dir) > 0)
// 			{
// 				color_hit = 
// 			}
// 		}
// 	}
// }


t_double3			raytracer(t_vector ray, t_scene *scene, void *to_ignore, int depth)
{
	t_surface		*surface;
	t_double3		color_hit;
	// t_vector		reflection;
	// t_double3		reflection_color;
	// t_vector		refraction;
	// t_double3		refraction_color;
	// double			kr;
	// t_double3		light_amount;
	// t_double3		specular_color;
	// t_vector		light;
	// int				test;

	if (depth > DEPTH_MAX)
		return ((t_double3){0.1, 0.1, 0.1});
	surface = intersect(ray, scene, to_ignore);
	if (surface == NULL)
		return ((t_double3){0.1, 0.1, 0.1});
	else
	{
		color_hit = surface->object->color;
		// if (surface->material == REFLECTION_AND_REFRACTION)
		// {
		// 	reflection.dir = normalize(reflect(ray.dir, surface->n_hit));
		// 	reflection.pos = (dot_product(reflection.dir, surface->n_hit) < 0) ?
		// 		vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
		// 		vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
		// 	refraction.dir = normalize(refract(ray.dir, surface->n_hit, surface->ior));
		// 	refraction.pos = (dot_product(refraction.dir, surface->n_hit) < 0) ?
		// 		vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
		// 		vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
		// 	reflection_color = raytracer(reflection, objects, to_ignore, depth + 1);
		// 	refraction_color = raytracer(refraction, objects, to_ignore, depth + 1);
		// 	fresnel(ray.dir, surface->n_hit, surface->ior, &kr);
		// 	color_hit = vec_plus_vec(scale_vec(reflection_color, kr),
		// 		vec_scale_vec(scale_vec(refraction_color, 1 - kr), surface->color));
		// }
		// else if (surface->material == REFLECTION)
		// {
		// 	// fresnel(ray.dir, surface->n_hit, surface->ior, &kr);
		// 	reflection.dir = reflect(ray.dir, surface->n_hit);
		// 	reflection.pos = (dot_product(reflection.dir, surface->n_hit) < 0) ?
		// 		vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
		// 		vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
		// 	color_hit = raytracer(reflection, objects, to_ignore, depth + 1);
		// }
		// else
		// {
			// t_light		*tmp;
			// int			i;
			// double		distance_squared;
			// double		light_dot_norm;
			// t_surface	*shadow_object;
			// int			in_shadow;

			// light_amount = (t_double3){0, 0, 0};
			// specular_color = (t_double3){0, 0, 0};
			// light.pos = (dot_product(ray.dir, surface->n_hit) < 0) ?
			// 	vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
			// 	vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
			// i = -1;
			// while (++i < objects->lights->length)
			// {
			// 	tmp = AG(t_light*, objects->lights, i);
			// 	light.dir = vec_minus_vec(tmp->pos, surface->p_hit);
			// 	distance_squared = dot_product(light.dir, light.dir);
			// 	light.dir = normalize(light.dir);
			// 	light_dot_norm = max_double(0.0, dot_product(light.dir, surface->n_hit));
			// 	if ((shadow_object = intersect(light, objects, to_ignore)) == NULL)
			// 		in_shadow = 0;
			// 	else
			// 	{
			// 		in_shadow = ((shadow_object->distance * shadow_object->distance) < distance_squared) ? 1 : 0;
			// 		free(shadow_object);
			// 	}
			// 	light_amount = vec_plus_vec(light_amount, scale_vec(scale_vec(tmp->color, (1 - in_shadow)), light_dot_norm));
			// 	reflection.dir = reflect(scale_vec(light.dir, -1), surface->n_hit);
			// 	specular_color = vec_plus_vec(specular_color, scale_vec(tmp->color, pow(max_double(0, -dot_product(reflection.dir, ray.dir)), 25)));
			// }
			// color_hit = vec_plus_vec(vec_scale_vec(scale_vec(light_amount, 0.8), surface->color), scale_vec(specular_color, 0.2));
		// }
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
			pixel_camera = rotation(pixel_camera, env->scene->camera.direction);
			color = raytracer((t_vector){env->scene->camera.position, pixel_camera}, env->scene, NULL, 0);
			color_standard(env, color, x, y);
		}
	}
}
