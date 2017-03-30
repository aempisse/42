#include "../rtv1.h"

static int 			intersect_plane(t_double3 origin, t_double3 dir, t_plane *plane, double *distance)
{
	double			denom;
	double			t;

	denom = dot_product(dir, plane->normal);
	t = -1;
	if (denom < 0.000001)
		return (0);
	else
	{
		t = dot_product(vec_minus_vec(origin, plane->pos), plane->normal) / denom;
		if (t < 0)
			return (0);
		*distance = t;
	}
	// ft_putendl("test");
	return (1);
}

static void			get_surface_plane(t_vector ray, t_plane *plane, t_surface **surface, double distance)
{
	if (*surface == NULL)
	{
		if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
			ft_error("Error : malloc() failed.\n");
	}
	(*surface)->distance = distance;
	(*surface)->p_hit = find_point(ray.pos, ray.dir, distance);
	(*surface)->n_hit = normalize(plane->normal);
	(*surface)->color = plane->color;
	(*surface)->ior = plane->ior;
	(*surface)->material = plane->material;
}

void					get_nearest_plane(t_vector ray, t_array *planes, t_surface **surface)
{
	t_plane			*tmp;
	t_plane			*nearest;
	double			distance;
	int				i;

	distance = 0;
	i = -1;
	while (++i < planes->length)
	{
		tmp = AG(t_plane*, planes, i);
		if (intersect_plane(ray.pos, ray.dir, tmp, &distance))
		{
			if (*surface == NULL)
				get_surface_plane(ray, tmp, surface, distance);
			else
			{
				if ((*surface)->distance > distance)
					get_surface_plane(ray, tmp, surface, distance);
			}
		}
	}
}