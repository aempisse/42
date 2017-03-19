#include "../rtv1.h"

void		add_num_plane(t_env *env)
{
	t_plane		*tmp;
	int			i;

	i = env->control->i;
	tmp = AG(t_plane*, env->plane, i);
	if (env->control->ctm_1 == 0)
		tmp->pos.x = env->control->num;
	if (env->control->ctm_1 == 1)
		tmp->pos.y = env->control->num;
	if (env->control->ctm_1 == 2)
		tmp->pos.z = env->control->num;
	if (env->control->ctm_1 == 3)
		tmp->normal.x = env->control->num;
	if (env->control->ctm_1 == 4)
		tmp->normal.y = env->control->num;
	if (env->control->ctm_1 == 5)
		tmp->normal.z = env->control->num;
}

void		add_num_sphere(t_env *env)
{
	t_sphere	*tmp;
	int			i;

	i = env->control->i;
	tmp = AG(t_sphere*, env->sphere, i);
	if (env->control->ctm_1 == 0)
		tmp->pos.x = env->control->num;
	if (env->control->ctm_1 == 1)
		tmp->pos.y = env->control->num;
	if (env->control->ctm_1 == 2)
		tmp->pos.z = env->control->num;
	if (env->control->ctm_1 == 3)
		tmp->radius = env->control->num;
}