#include "../rtv1.h"


// op->v = ft_unit_vector(obj->rot);
// op->dv = ft_dot(ray.dir, op->v);	dot_product(dir, cone->dir)
// op->x = ft_sub(ray.o, obj->pos);	vec_minus_vec(origin, cone->pos)
// op->xv = ft_dot(op->x, op->v);		dot_product(vec_minus_vec(origin, cone->pos), cone->dir)
// op->a = ft_dot(ray.dir, ray.dir) - ((1 + obj->radius * obj->radius) * (op->dv * op->dv));
// op->b = (ft_dot(ray.dir, op->x) - ((1 + obj->radius * obj->radius) * (op->dv * op->xv))) * 2.0;
// op->c = ft_dot(op->x, op->x) - ((1 + obj->radius * obj->radius) * (op->xv * op->xv));
// op->delta = (op->b * op->b) - (4 * op->a * op->c);


static int				intersect_cone(t_double3 origin, t_double3 dir, t_cone *cone, double *distance)
{
	double			angle;
	double			a;
	double			b;
	double			c;
	double 			discr;
	double			t0;
	double			t1;

	cone->dir = normalize(cone->dir);
	angle = cone->aperture * (PI / 180.0);

	a = dot_product(dir, dir) - (2 * dot_product(dir, cone->dir) *
		dot_product(dir, cone->dir));
	b = 2 * (dot_product(dir, vec_minus_vec(origin, cone->pos)) - (2 *
		(dot_product(dir, cone->dir) * dot_product(vec_minus_vec(origin, cone->pos), cone->dir))));
	c = dot_product(vec_minus_vec(origin, cone->pos), vec_minus_vec(origin, cone->pos)) -
		(2 * (dot_product(vec_minus_vec(origin, cone->pos), cone->dir) *
		dot_product(vec_minus_vec(origin, cone->pos), cone->dir)));





	// a = dir.x * dir.x + dir.z * dir.z - dir.y * dir.y * tan(angle) * tan(angle);
	// b = 2 * (origin.x * dir.x + origin.z * dir.z - dir.x * cone->pos.x - dir.z * cone->pos.z
	// 	+ (dir.y * (cone->pos.y - origin.y)) * tan(angle) * tan(angle));
	// c = origin.x * origin.x + origin.z * origin.z + cone->pos.x * cone->pos.x + cone->pos.z
	// 	* cone->pos.z - 2 * (origin.x * cone->pos.x + origin.z * cone->pos.z + origin.z * cone->pos.z)
	// 	- (origin.y * origin.y - 2 * (origin.y * cone->pos.y) + cone->pos.y * cone->pos.y) * tan(angle) * tan(angle);
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

static void			get_surface_cone(t_vector ray, t_cone *cone, t_surface **surface, double distance)
{
	if (*surface == NULL)
	{
		if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
			ft_error("Error : malloc() failed.\n");
	}
	(*surface)->object = (void*)cone;
	(*surface)->distance = distance;
	(*surface)->p_hit = find_point(ray.pos, ray.dir, distance);
	(*surface)->n_hit = normalize(vec_minus_vec((*surface)->p_hit, cone->pos));
	(*surface)->color = cone->color;
	(*surface)->ior = cone->ior;
	(*surface)->material = cone->material;
}

void				get_nearest_cone(t_vector ray, t_array *cones, t_surface **surface, void *to_ignore)
{
	t_cone			*tmp;
	double			distance;
	int				i;

	distance = 0;
	i = -1;
	while (++i < cones->length)
	{
		tmp = AG(t_cone*, cones, i);
		if ((void*)tmp != to_ignore && intersect_cone(ray.pos, ray.dir, tmp, &distance))
		{
			if (*surface == NULL)
				get_surface_cone(ray, tmp, surface, distance);
			else
			{
				if ((*surface)->distance > distance)
					get_surface_cone(ray, tmp, surface, distance);
			}
		}
	}
}