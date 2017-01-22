#include "../rtv1.h"

static void	init_new_obj_sphere(t_env *env)
{
	t_sphere	*tmp;

	tmp = (t_sphere*)malloc(sizeof(t_sphere));
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->radius = 0;
	ft_array_add(env->sphere, tmp);
	env->control->i = env->sphere->length - 1;
}

static void	init_new_obj_disk(t_env *env)
{
	t_sphere	*tmp;

	tmp = (t_disk*)malloc(sizeof(t_disk));
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	tmp->radius = 0;
	ft_array_add(env->disk, tmp);
	env->control->i = env->disk->length - 1;
}

static void	init_new_obj_plane(t_env *env)
{
	t_plane		*tmp;

	tmp = (t_plane*)malloc(sizeof(t_plane));
	tmp->pos.x = 0;
	tmp->pos.y = 0;
	tmp->pos.z = 0;
	ft_array_add(env->plane, tmp);
	env->control->i = env->plane->length - 1;
}

void		init_new_obj(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
		init_new_obj_sphere(env);
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
		init_new_obj_plane(env);
	if (ft_strcmp(env->control->name_obj, "Disk") == 0)
		init_new_obj_disk(env);
}