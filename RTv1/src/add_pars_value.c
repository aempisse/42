#include "../rtv1.h"

void			add_light_value(t_env *env, t_double3 *values, int i)
{
	t_light		*tmp;

	tmp = AG(t_light*, env->objects->lights, env->i_light);
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->color = *values;
}

void			add_cone_value(t_env *env, t_double3 *values, int i)
{
	t_cone		*tmp;

	tmp = AG(t_cone*, env->objects->cone, env->i_cone);
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->normal = *values;
	else if (i == 2)
		tmp->aperture = values->x;
	else if (i == 3)
		tmp->color = *values;
	else if (i == 4)
		tmp->ior = values->x;
	else if (i == 5)
		tmp->material = values->x;
}

void			add_cylinder_value(t_env *env, t_double3 *values, int i)
{
	t_cylinder		*tmp;

	tmp = AG(t_cylinder*, env->objects->cylinder, env->i_cylinder);
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->normal = *values;
	else if (i == 2)
		tmp->radius = values->x;
	else if (i == 3)
		tmp->color = *values;
	else if (i == 4)
		tmp->ior = values->x;
	else if (i == 5)
		tmp->material = values->x;
}

void			add_plane_value(t_env *env, t_double3 *values, int i)
{
	t_plane		*tmp;

	tmp = AG(t_plane*, env->objects->planes, env->i_plane);
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->normal = *values;
	else if (i == 2)
		tmp->color = *values;
	else if (i == 3)
		tmp->ior = values->x;
	else if (i == 4)
		tmp->material = values->x;
}

void			add_sphere_value(t_env *env, t_double3 *values, int i)
{
	t_sphere	*tmp;

	tmp = AG(t_sphere*, env->objects->spheres, env->i_sphere);
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->radius = values->x;
	else if (i == 2)
		tmp->color = *values;
	else if (i == 3)
		tmp->ior = values->x;
	else if (i == 4)
		tmp->material = values->x;
}
