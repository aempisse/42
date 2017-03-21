#include "../rtv1.h"

static int 			intersect_plane(t_double3 origin, t_double3 dir, t_plane *plane, double *distance)
{
	double			denom;

	plane->normal = normalize(plane->normal);
	denom = dot_product(dir, plane->normal);
	if (denom > 0.00001)
		*distance = dot_product(vec_minus_vec(origin.pos, plane->pos)
		, plane->normal) / denom;
	else
		return (0);
	return (1);
}

static void			get_surface_plane(t_vector ray, t_plane *plane, t_surface *surface)
{
	surface->p_hit = find_point(ray.pos, ray.dir, surface->distance);
	surface->n_hit = normalize(plane->normal);
	surface->color = plane->color;
	surface->ior = plane->ior;
	surface->material = plane->material;
}

int					get_nearest_plane(t_vector ray, t_array *planes, t_surface *surface)
{
	t_plane			*tmp;
	t_plane			*nearest;
	double			distance;
	int				new;
	int				i;

	new = 0;
	distance = -1;
	i = -1;
	while (++i < planes->length)
	{
		tmp = AG(t_plane*, planes, i);
		if (intersect_plane(ray.pos, ray.dir, tmp, &distance))
		{
			if (distance > 0 && (surface->distance == -1 || surface->distance > distance))
			{
				new = 1;
				nearest = tmp;
				surface->distance = distance;
			}
		}
	}
	if (new)
		get_surface_plane(ray, nearest, surface);
	return (new);
}