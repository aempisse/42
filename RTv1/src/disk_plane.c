#include "../rtv1.h"

static t_plane		*init_disk_plane(t_env *env, t_plane *plane, t_disk *disk)
{
	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->pos.x = disk->pos.x;
	plane->pos.y = disk->pos.y;
	plane->pos.z = disk->pos.z;
	plane->normal.x = disk->normal.x;
	plane->normal.y = disk->normal.y;
	plane->normal.z = disk->normal.z;
	return (plane);
}

int				intersect_disk(t_env *env, t_double3 dir, t_disk *disk, double *distance)
{
	t_double3	inter_p;
	t_double3	vec;
	t_plane		*plane;

	plane = init_disk_plane(env, plane, disk);
	if (intersect_plane(env, dir, plane, distance))
	{
		inter_p.x = env->camera.pos.x + dir.x * *distance;
		inter_p.y = env->camera.pos.y + dir.y * *distance;
		inter_p.z = env->camera.pos.z + dir.z * *distance;
		vec.x = inter_p.x - disk->pos.x;
		vec.y = inter_p.y - disk->pos.y;
		vec.z = inter_p.z - disk->pos.z;
		*distance = dot_product(vec, vec);
		if (*distance <= disk->radius * disk->radius)
			return (1);
	}
	return (0);
}

int 			intersect_plane(t_env *env, t_double3 dir, t_plane *plane, double *distance)
{
	double 		denom;
	t_double3	normal_plane;
	t_double3	center;

	center.x = env->camera.pos.x - plane->pos.x;
	center.y = env->camera.pos.y - plane->pos.y;
	center.z = env->camera.pos.z - plane->pos.z;
	normal_plane = normalize(plane->normal);
	denom = dot_product(dir, normal_plane);
	if (denom > 0.00001)
		*distance = dot_product(center, normal_plane) / denom;
	else
		return (0);
	return (1);
}