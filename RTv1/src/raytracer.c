#include "../rtv1.h"

int					intersect(t_vector ray, t_objects *objects, t_surface *surface)
{
	int				intersection;

	if ((surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
		ft_error("Error : malloc() failed.\n");
	surface->distance = -1;
	intersection = get_nearest_sphere(ray, objects->spheres, surface);
	intersection = get_nearest_plane(ray, objects->planes, surface);
	return (intersection);
}

t_double3			reflect(t_double3 incidence, t_double3 normal)
{
	t_double3		reflect;

	reflect.x = incidence.x - 2 * dot_product(incidence, normal) * normal.x;
	reflect.y = incidence.y - 2 * dot_product(incidence, normal) * normal.y;
	reflect.z = incidence.z - 2 * dot_product(incidence, normal) * normal.z;
	return (reflect);
}

t_double3			refract(t_double3 incidence, t_double3 normal, double ior)
{
	t_double3		refract;
	double			cosi;
	double			etai;
	double			etat;
	double			eta;
	double			k;

	cosi = max_double(-1.0, min_double(1.0, dot_product(incidence, normal)));
	etai = 1;
	etat = ior;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		swap(&etai, &etat);
		normal = vec_minus_vec((t_double3){0, 0, 0}, normal);
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	refract = k < 0 ? (t_double3){0, 0, 0} : (t_double3){
	eta * incidence.x + (eta * cosi - sqrt(k)) * normal.x,
	eta * incidence.y + (eta * cosi - sqrt(k)) * normal.y,
	eta * incidence.z + (eta * cosi - sqrt(k)) * normal.z};
	return (refract);
}

t_double3			fresnel(t_double3 incidence, t_double3 normal, double ior, double *kr)
{
	double			cosi;
	double			etai;
	double			etat;
	double			sint;
	double			k;
	double			cost;
	double			rs;
	double			rp;

	cosi = max_double(-1.0, min_double(1.0, dot_product(incidence, normal)));
	etai = 1;
	etat = ior;
	if (cosi > 0)
		swap(&etai, &etat);
	sint = etai / etat * sqrt(max_double(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*kr = 1;
	else
	{
		cost = sqrt(max_double(0.0, 1 - sint * sint));
		cosi = cosi > 0 ? cosi : -cosi;
		rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (rs * rs + rp * rp) / 2.0;
	}
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

	if (depth > DEPTH_MAX || !intersect(ray, objects, surface))
		return ((t_double3){1, 1, 1});
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
		color_hit = vec_plus_vec(scale_vec(reflection_color, kr), scale_vec(refraction_color, 1 - kr));
	}
	else if (surface->material == REFLECTION)
	{
		fresnel(ray.dir, surface->n_hit, surface->ior, &kr);
		reflection.dir = reflect(ray.dir, surface->n_hit);
		reflection.pos = (dot_product(reflection.dir, surface->n_hit) < 0) ?
			vec_minus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS)) :
			vec_plus_vec(surface->p_hit, scale_vec(surface->n_hit, BIAS));
		color_hit = raytracer(reflection, objects, depth + 1);
	}
	else
	{
		/*
		** Phong illumination model
		*/
	}
	return (color_hit);
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
			rgb_color.b.a = 0xFF;
			rgb_color.b.r = 255 * max_double(0, min_double(1, color.x));
			rgb_color.b.g = 255 * max_double(0, min_double(1, color.y));
			rgb_color.b.b = 255 * max_double(0, min_double(1, color.z));
			color_pixel_image(rgb_color, (WIDTH * y + x) * env->img->opp, env->img);
		}
	}
}