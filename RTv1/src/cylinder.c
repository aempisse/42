#include "../rtv1.h"

	// op->v = ft_unit_vector(obj->rot);
	// op->x = ft_sub(ray.o, obj->pos);	vec_minus_vec(origin - cylinder->pos)
	// op->dv = ft_dot(ray.dir, op->v);	dot_product(dir, cylinder->dir)
	// op->xv = ft_dot(op->x, op->v);		dot_product(vec_minus_vec(origin - cylinder->pos), cylinder->dir)
	// op->a = ft_dot(ray.dir, ray.dir) - (op->dv * op->dv);
	// op->b = (ft_dot(ray.dir, op->x) - (op->dv * op->xv)) * 2.0;
	// op->c = ft_dot(op->x, op->x) - (op->xv * op->xv) -
	// 	(obj->radius * obj->radius);
	// op->delta = (op->b * op->b) - (4 * op->a * op->c);

static int				intersect_cylinder(t_double3 origin, t_double3 dir, t_cylinder *cylinder, double *distance)
{
	double			a;
	double			b;
	double			c;
	double 			discr;
	double			t0;
	double			t1;

	cylinder->dir = normalize(cylinder->dir);
	a = dot_product(dir, dir) - dot_product(dir, cylinder->dir) * dot_product(dir, cylinder->dir);
	b = 2 * (dot_product(dir, vec_minus_vec(origin, cylinder->pos)) - (dot_product(dir, cylinder->dir) *
		dot_product(vec_minus_vec(origin, cylinder->pos), cylinder->dir)));
	c = dot_product(vec_minus_vec(origin, cylinder->pos), vec_minus_vec(origin, cylinder->pos)) -
		dot_product(vec_minus_vec(origin, cylinder->pos), cylinder->dir) *
		dot_product(vec_minus_vec(origin, cylinder->pos), cylinder->dir) -
		(cylinder->radius * cylinder->radius);

	// a = dir.x * dir.x + dir.z * dir.z;
	// b = 2 * (origin.x * dir.x + origin.z * dir.z - dir.x * cylinder->pos.x - dir.z * cylinder->pos.z);
	// c = origin.x * origin.x + origin.z * origin.z + cylinder->pos.x * cylinder->pos.x + cylinder->pos.z
	// 	* cylinder->pos.z - cylinder->radius * cylinder->radius - 2 * (origin.x * cylinder->pos.x +
	// 	origin.z * cylinder->pos.z);
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

static t_double3	get_normal_cylinder(t_double3 point, t_cylinder *cylinder)
{
	t_double3		normal;

	normal.x = point.x - cylinder->pos.x;
	normal.y = point.y;
	normal.z = point.z - cylinder->pos.z;
	return (normalize(normal));
}

static void			get_surface_cylinder(t_vector ray, t_cylinder *cylinder, t_surface **surface, double distance)
{
	if (*surface == NULL)
	{
		if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
			ft_error("Error : malloc() failed.\n");
	}
	(*surface)->object = (void*)cylinder;
	(*surface)->distance = distance;
	(*surface)->p_hit = find_point(ray.pos, ray.dir, distance);
	(*surface)->n_hit = get_normal_cylinder((*surface)->p_hit, cylinder);
	(*surface)->color = cylinder->color;
	(*surface)->ior = cylinder->ior;
	(*surface)->material = cylinder->material;
}

void				get_nearest_cylinder(t_vector ray, t_array *cylinders, t_surface **surface, void *to_ignore)
{
	t_cylinder		*tmp;
	double			distance;
	int				i;

	distance = 0;
	i = -1;
	while (++i < cylinders->length)
	{
		tmp = AG(t_cylinder*, cylinders, i);
		if ((void*)tmp != to_ignore && intersect_cylinder(ray.pos, ray.dir, tmp, &distance))
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