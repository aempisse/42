#include "../rtv1.h"

int				intersect_sphere(t_double3 origin, t_double3 dir, t_sphere *sphere, double *distance)
{
	t_double3	center;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		t0;
	double		t1;

	center = vec_minus_vec(origin, sphere->pos);
	a = dot_product(dir, dir);
	b = 2 * dot_product(dir, center);
	c = dot_product(center, center) - sphere->radius * sphere->radius;
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else
	{
		t0 = (- b - sqrt(discr)) / (2 * a);
		t1 = (- b + sqrt(discr)) / (2 * a);
		if (t0 > t1)
			swap(&t0, &t1);
		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
				return (0);
		}
		*distance = t0;
	}
	return (1);
}

t_double3	raytracer(t_double3 ray_origin, t_double3 ray_dir, t_array *spheres, int depth)
{

/*
**	La nouvelle fonction de tracage. Elle prend en paramètre un rayon, défini par
**	son origine et sa direction. On calcule si ce rayon traverse une sphère.
**	Si c'est le cas on calcule le point d'intersection, la normale au point d'intersection,
**	et grâce à ces informations on calcule la couleur. Cette nuance dépend des propriétés
**	de la sphère (transparence, reflection, diffusion, etc...). Si la sphère réfléchie
**	la lumière, la nuance de couleur dépend aussi des sphères autour donc on trace
**	un nouveau rayon qui dépend de la normale du point d'intersection.
**	Si la sphère est transparente on trace un rayon qui traverse la sphère.
**	La variable depth en paramètre sert à limiter la profondeur de la récursion,
**	si on ne la limitait pas on pourrait avoir des rayons qui se renvoient à l'infini.
**	La fonction retourn une vecteur dont les coefficients décrivent une couleur.
*/

	t_sphere	*tmp;
	t_sphere	*tmp2;
	t_sphere	*sphere;
	double		nearest;
	double		distance;
	int			i;
	int			j;

	t_double3	surface_color;
	t_double3	point_hit;
	t_double3	normal_hit;
	int			inside;
	double		facing_ratio;
	double		fresnel;
	t_double3	reflection_dir;
	t_double3	reflection;
	t_double3	refraction_dir;
	t_double3	refraction;
	double		ior;
	double		eta;
	double		cosi;
	double		k;

	t_double3	transmission;
	t_double3	light_dir;

	nearest = -1;
	i = -1;
	while (++i < spheres->length)
	{
		tmp = AG(t_sphere*, spheres, i);
		if (intersect_sphere(ray_origin, ray_dir, tmp, &distance))
		{
			if (nearest == -1 || nearest > distance)
			{
				nearest = distance;
				sphere = tmp;
			}
		}
	}
	if (nearest == -1)
		return ((t_double3){1, 1, 1});

	surface_color = (t_double3){0, 0, 0};
	point_hit = find_point(ray_origin, ray_dir, nearest);
	normal_hit = normalize(vec_minus_vec(point_hit, sphere->pos));
	inside = 0;
	if (dot_product(ray_dir, normal_hit) > 0)
	{
		normal_hit = vec_minus_vec((t_double3){0, 0, 0}, normal_hit);
		inside = 1;
	}
	if ((sphere->transparency > 0 || sphere->reflectivity > 0) && depth < DEPTH)
	{
		facing_ratio = dot_product(vec_minus_vec((t_double3){0, 0, 0}, ray_dir), normal_hit);
		fresnel = fresnel_effect(pow(1 - facing_ratio, 3), 1, 0.1);
		reflection_dir.x = ray_dir.x - normal_hit.x * 2 * dot_product(ray_dir, normal_hit);
		reflection_dir.y = ray_dir.y - normal_hit.y * 2 * dot_product(ray_dir, normal_hit);
		reflection_dir.z = ray_dir.z - normal_hit.z * 2 * dot_product(ray_dir, normal_hit);
		reflection_dir = normalize(reflection_dir);
		reflection = raytracer(find_point(point_hit, normal_hit, 0.0001), reflection_dir, spheres, depth + 1);
		
		refraction = (t_double3){0, 0, 0};
		if (sphere->transparency)
		{
			ior = 1.1;
			eta = inside ? ior : 1 / ior;
			cosi = dot_product(vec_minus_vec((t_double3){0, 0, 0}, normal_hit), ray_dir);
			k = 1 - eta * eta * (1 - cosi * cosi);
			refraction_dir.x = ray_dir.x * eta + normal_hit.x * (eta * cosi - sqrt(k));
			refraction_dir.y = ray_dir.y * eta + normal_hit.y * (eta * cosi - sqrt(k));
			refraction_dir.z = ray_dir.z * eta + normal_hit.z * (eta * cosi - sqrt(k));
			refraction_dir = normalize(refraction_dir);
			refraction = raytracer(find_point(point_hit, normal_hit, 0.0001), refraction_dir, spheres, depth + 1);
		}
		surface_color.x = reflection.x * fresnel + refraction.x * (1 - fresnel) * sphere->transparency * sphere->color.x;
		surface_color.y = reflection.y * fresnel + refraction.y * (1 - fresnel) * sphere->transparency * sphere->color.y;
		surface_color.z = reflection.z * fresnel + refraction.z * (1 - fresnel) * sphere->transparency * sphere->color.z;
	}
	else
	{
		i = -1;
		while (++i < spheres->length)
		{
			tmp = AG(t_sphere*, spheres, i);
			if (tmp->emission.x > 0)
			{
				transmission = (t_double3){1, 1, 1};
				light_dir = vec_minus_vec(tmp->pos, point_hit);
				light_dir = normalize(light_dir);
				j = -1;
				while (++j < spheres->length)
				{
					tmp2 = AG(t_sphere*, spheres, i);
					if (tmp != tmp2)
					{
						if (intersect_sphere(find_point(point_hit, normal_hit, 0.0001), light_dir, tmp2, &distance))
						{
							transmission = (t_double3){0, 0, 0};
							break;
						}
					}
				}
				surface_color.x += sphere->color.x * transmission.x * max_double(0.0, dot_product(normal_hit, light_dir)) * tmp->emission.x;
				surface_color.y += sphere->color.y * transmission.y * max_double(0.0, dot_product(normal_hit, light_dir)) * tmp->emission.y;
				surface_color.z += sphere->color.z * transmission.z * max_double(0.0, dot_product(normal_hit, light_dir)) * tmp->emission.z;
			}
		}
	}
	return ((t_double3){surface_color.x + sphere->color.x,
						surface_color.y + sphere->color.y,
						surface_color.z + sphere->color.z});
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
	scale = tan((env->fov * 0.5 * PI) / 180.0);
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
			color = raytracer(env->camera.pos, pixel_camera, env->sphere, 0);
			rgb_color.b.a = 0xFF;
			rgb_color.b.r = 255 * color.x;
			rgb_color.b.g = 255 * color.y;
			rgb_color.b.b = 255 * color.z;
			color_pixel_image(rgb_color, (WIDTH * y + x) * env->img->opp, env->img);
		}
	}
}
