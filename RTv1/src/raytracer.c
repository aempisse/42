#include "../rtv1.h"

t_surface			*intersect(t_vector ray, t_objects *objects)
{
	t_surface		*surface;

	surface = NULL;
	get_nearest_plane(ray, objects->planes, &surface);
	get_nearest_sphere(ray, objects->spheres, &surface);
	//get_nearest_cylinder(ray, objects->cylinder, &surface);
	return (surface);
}

t_double3			raytracer(t_vector ray, t_objects *objects, int depth)
{
	t_surface		*surface;
	t_double3		color_hit;
	t_vector		reflection;
	t_double3		reflection_color;
	t_vector		refraction;
	t_double3		refraction_color;
	double			kr;
	t_double3		light_amount;
	t_double3		specular_color;
	t_vector		light;
	int				test;

	if (depth > DEPTH_MAX)
		return ((t_double3){0.1, 0.1, 0.3});
	surface = intersect(ray, objects);
	if (surface == NULL)
		return ((t_double3){0.1, 0.1, 0.3});
	else
	{
		if (surface->material == REFLECTION_AND_REFRACTION)
		{
			reflection.dir = normalize(reflect(ray.dir, surface->n_hit));
			reflection.pos = (dot_product(reflection.dir, surface->n_hit) < 0) ?
				vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
				vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
			refraction.dir = normalize(refract(ray.dir, surface->n_hit, surface->ior));
			refraction.pos = (dot_product(refraction.dir, surface->n_hit) < 0) ?
				vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
				vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
			reflection_color = raytracer(reflection, objects, depth + 1);
			refraction_color = raytracer(refraction, objects, depth + 1);
			fresnel(ray.dir, surface->n_hit, surface->ior, &kr);
			color_hit = vec_plus_vec(scale_vec(reflection_color, kr),
				vec_scale_vec(scale_vec(refraction_color, 1 - kr), surface->color));
		}
		else if (surface->material == REFLECTION)
		{
			fresnel(ray.dir, surface->n_hit, surface->ior, &kr);
			reflection.dir = reflect(ray.dir, surface->n_hit);
			reflection.pos = (dot_product(reflection.dir, surface->n_hit) < 0) ?
				vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
				vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
			color_hit = raytracer(reflection, objects, depth + 1);
		}
		else
		{
			t_light		*tmp;
			int			i;
			double		distance_squared;
			double		light_dot_norm;
			t_surface	*shadow_object;
			int			in_shadow;

			light_amount = (t_double3){0, 0, 0};
			specular_color = (t_double3){0, 0, 0};
			light.pos = (dot_product(ray.dir, surface->n_hit) < 0) ?
				vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
				vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
			i = -1;
			while (++i < objects->lights->length)
			{
				tmp = AG(t_light*, objects->lights, i);
				light.dir = vec_minus_vec(tmp->pos, surface->p_hit);
				distance_squared = dot_product(light.dir, light.dir);
				light.dir = normalize(light.dir);
				light_dot_norm = max_double(0.0, dot_product(light.dir, surface->n_hit));
				if ((shadow_object = intersect(light, objects)) == NULL)
					in_shadow = 0;
				else
				{
					in_shadow = ((shadow_object->distance * shadow_object->distance) < distance_squared) ? 1 : 0;
					free(shadow_object);
				}
				light_amount = vec_plus_vec(light_amount, scale_vec(scale_vec(tmp->color, (1 - in_shadow)), light_dot_norm));
				reflection.dir = reflect(scale_vec(light.dir, -1), surface->n_hit);
				specular_color = vec_plus_vec(specular_color, scale_vec(tmp->color, pow(max_double(0, -dot_product(reflection.dir, ray.dir)), 25)));
			}
			color_hit = vec_plus_vec(vec_scale_vec(scale_vec(light_amount, 0.8), surface->color), scale_vec(specular_color, 0.2));
		}
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
	t_color		rgb_color;

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
			color = raytracer((t_vector){env->camera.pos, pixel_camera}, env->objects, 0);
			rgb_color.b.a = 0x00;
			rgb_color.b.r = 255 * max_double(0, min_double(1, color.x));
			rgb_color.b.g = 255 * max_double(0, min_double(1, color.y));
			rgb_color.b.b = 255 * max_double(0, min_double(1, color.z));
			color_pixel_image(rgb_color, (WIDTH * y + x) * env->img->opp, env->img);
			mlx_pixel_put(env->mlx, env->win_scene, x, y, 0xFFFFFFFF);
		}
	}
}