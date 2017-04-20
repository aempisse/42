#include "../rtv1.h"

void		add_light_value(t_env *env, t_double3 *values, int i)
{
	t_light	*tmp;

	tmp = env->scene->light;
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->dir = *values;
}

void		add_value(t_env *env, t_double3 *values, int i)
{
	t_object	*tmp;

	tmp = env->scene->object;
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->rotation = *values;
	else if (i == 2)
		tmp->radius = values->x;
	else if (i == 4)
		tmp->dcp_min = *values;
	else if (i == 5)
		tmp->dcp_max = *values;
}
