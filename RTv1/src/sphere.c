#include "../rtv1.h"

static int			intersect_sphere(t_double3 origin, t_double3 dir, t_sphere *sphere, double *distance)
{
	t_double3	center;
	double		a;
	double		b;
	double		c;
	double		discr;
	double		t0;
	double		t1;
	double		tmp;

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

static void			get_surface_sphere(t_vector ray, t_sphere *sphere, t_surface **surface, double distance)
{
	if (*surface == NULL)
	{
		if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
			ft_error("Error : malloc() failed.\n");
	}
	(*surface)->distance = distance;
	(*surface)->p_hit = find_point(ray.pos, ray.dir, distance);
	(*surface)->n_hit = normalize(vec_minus_vec((*surface)->p_hit, sphere->pos));
	(*surface)->color = sphere->color;
	(*surface)->ior = sphere->ior;
	(*surface)->material = sphere->material;
}

void				get_nearest_sphere(t_vector ray, t_array *spheres, t_surface **surface)
{
	t_sphere		*tmp;
	t_sphere		*nearest;
	double			distance;
	int				i;

	distance = 0;
	i = -1;
	while (++i < spheres->length)
	{
		tmp = AG(t_sphere*, spheres, i);
		if (intersect_sphere(ray.pos, ray.dir, tmp, &distance))
		{
			if (*surface == NULL)
				get_surface_sphere(ray, tmp, surface, distance);
			else
			{
				if ((*surface)->distance > distance)
					get_surface_sphere(ray, tmp, surface, distance);
			}
		}
	}
	// if (surface == NULL)
	// 	return (0);
	// return (1);
}