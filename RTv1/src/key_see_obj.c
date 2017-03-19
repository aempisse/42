#include "../rtv1.h"

static int		chang_obj(int keycode, t_env *env)
{
	if (keycode == KEY_RIGHT && ft_strcmp(env->control->name_obj, "Sphere") == 0 &&
	 	env->control->i < env->sphere->length - 1)
		env->control->i++;
	if (keycode == KEY_LEFT && ft_strcmp(env->control->name_obj, "Sphere") == 0 &&
		env->control->i > 0)
		env->control->i--;
	if (keycode == KEY_RIGHT && ft_strcmp(env->control->name_obj, "Plane") == 0 &&
 		env->control->i < env->plane->length - 1)
		env->control->i++;
	if (keycode == KEY_LEFT && ft_strcmp(env->control->name_obj, "Plane") == 0 &&
	 	env->control->i > 0)
		env->control->i--;
	return (0);
}

static void		incr_ctm(int keycode, t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
	{
		if (keycode == KEY_DOWN && env->control->ctm_1 < 5)
			env->control->ctm_1++;
		if (keycode == KEY_UP && env->control->ctm_1 > 0)
			env->control->ctm_1--;
	}
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
	{
		if (keycode == KEY_DOWN && env->control->ctm_1 < 3)
			env->control->ctm_1++;
		if (keycode == KEY_UP && env->control->ctm_1 > 0)
			env->control->ctm_1--;
	}
	env->control->neg = 1;
	env->control->num = 0;
	env->control->stop_add = 0;
}

int			key_new_obj_in(int keycode, t_env *env)
{
	if (keycode == KEY_ENTER)
	{
		env->control->menu = 0;
		env->control->ctm_1 = 0;
		env->control->i = 0;
		env->control->stop_add = 0;
		env->control->num = 0;
	}
	if (keycode == KEY_DOWN || keycode == KEY_UP)
	{
		incr_ctm(keycode, env);
		env->control->num = 0;
		env->control->stop_add = 0;
	}
	key_add(keycode, env);
	return (0);
}

int			key_obj_in(int keycode, t_env *env)
{
	if (keycode == KEY_M)
		env->control->mod = env->control->mod == 0 ? 1 : 0;
	if (env->control->mod == 0)
	{
		if (keycode == KEY_ESC)
		{
			env->control->menu = 1;
			env->control->ctm_1 = 0;
			env->control->i = 0;
			env->control->stop_add = 0;
		}
		if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
			chang_obj(keycode, env);
	}
	if (env->control->mod == 1)
	{
		if (keycode == KEY_DOWN || keycode == KEY_UP)
		{
			incr_ctm(keycode, env);
			env->control->stop_add = 0;
		}
		key_add(keycode, env);
	}
	return (0);
}
