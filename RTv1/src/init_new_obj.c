#include "../rtv1.h"

static void	init_new_obj_sphere(t_env *env)
{
	t_sphere	*tmp;

	tmp = (t_sphere*)malloc(sizeof(t_sphere));
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->radius = 0;
	ft_array_add(env->objects->spheres, tmp);
	env->control->i = env->objects->spheres->length - 1;
}

static void	init_new_obj_plane(t_env *env)
{
	t_plane		*tmp;

	tmp = (t_plane*)malloc(sizeof(t_plane));
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->normal.x = 0;
	tmp->normal.y = 0;
	tmp->normal.z = 0;
	ft_array_add(env->objects->planes, tmp);
	env->control->i = env->objects->planes->length - 1;
}

void		init_new_obj(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
		init_new_obj_sphere(env);
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
		init_new_obj_plane(env);
}