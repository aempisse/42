#include "../rtv1.h"

static int				intersect_cylinder(t_double3 origin, t_double3 dir, t_cylinder *cylinder, double *distance)
{
	t_double3		pos;
	double			a;
	double			b;
	double			c;
	double 			discr;
	t_double3 			tmp;
	double			t0;
	double			t1;

	pos = vec_minus_vec(origin, cylinder->pos);
	tmp = vec_minus_vec(dir, scale_vec(cylinder->normal, dot_product(dir, cylinder->normal)));
	a = dot_product(tmp, tmp);
	tmp = vec_minus_vec(dir, vec_scale_vec(pos, vec_scale_vec(cylinder->normal, vec_scale_vec(cylinder->normal, dir)));
	b = scale_vec((vec_minus_vec(tmp, vec_minus_vec(pos, vec_scale_vec(cylinder->normal,
	vec_scale_vec(cylinder->normal, pos))))), 2);
	c = sqrt(vec_minus_vec(pos, dot_product(cylinder->normal,
	dot_product(pos, cylinder->normal)))) - sqrt(cylinder->radius);
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

static void			get_surface_cylinder(t_vector ray, t_cylinder *cylinder, t_surface **surface, double distance)
{
	if (*surface == NULL)
	{
		if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
			ft_error("Error : malloc() failed.\n");
	}
	(*surface)->distance = distance;
	(*surface)->p_hit = find_point(ray.pos, ray.dir, distance);
	(*surface)->n_hit = normalize(vec_minus_vec((*surface)->p_hit, cylinder->pos));
	(*surface)->color = cylinder->color;
	(*surface)->ior = cylinder->ior;
	(*surface)->material = cylinder->material;
}

void				get_nearest_cylinder(t_vector ray, t_array *cylinder, t_surface **surface)
{
	t_cylinder		*tmp;
	t_cylinder		*nearest;
	double			distance;
	int				i;

	distance = 1000000000;
	i = -1;
	while (++i < cylinder->length)
	{
		tmp = AG(t_cylinder*, cylinder, i);
		if (intersect_cylinder(ray.pos, ray.dir, tmp, &distance))
		{
			if (*surface == NULL)
				get_surface_cylinder(ray, tmp, surface, distance);
			else
			{
				if ((*surface)->distance > distance)
					get_surface_cylinder(ray, tmp, surface, distance);
			}
		}
	}
}