#include "../rtv1.h"

void		init_light_obj(t_env *env)
{
	t_light	*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->pos.x = 0;
	light->pos.y = 0;
	light->pos.z = 0;
	light->color.x = 0;
	light->color.y = 0;
	light->color.z = 0;
	env->i_light++;
	ft_array_add(env->objects->lights, light);
}
