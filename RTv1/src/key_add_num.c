#include "../rtv1.h"

char			*search_type_obj(int c)
{
	char	*str;

	if (c == 0)
		str = "Sphere";
	if (c == 1)
		str = "Plane";
	if (c == 2)
		str = "Disk";
	return (str);
}

static void	add_to_struct(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
		add_num_sphere(env);
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
		add_num_plane(env);
	if (ft_strcmp(env->control->name_obj, "Disk") == 0)
		add_num_disk(env);
}

static void	add_num(t_env *env, double num)
{
	if (env->control->num < 0)
		env->control->num = env->control->num * -1;
	if (env->control->stop_add == 0)
	{
		env->control->num = num;
		env->control->stop_add = 1;
	}
	else if (env->control->stop_add == 1 && env->control->num < 1000)
		env->control->num = env->control->num * 10 + num;
	env->control->num = env->control->num * env->control->neg;
	add_to_struct(env);
}

static void	key_num(int keycode, t_env *env)
{
	if (keycode == KEY_0)
		add_num(env, 0);
	if (keycode == KEY_1)
		add_num(env, 1);
	if (keycode == KEY_2)
		add_num(env, 2);
	if (keycode == KEY_3)
		add_num(env, 3);
	if (keycode == KEY_4)
		add_num(env, 4);
	if (keycode == KEY_5)
		add_num(env, 5);
	if (keycode == KEY_6)
		add_num(env, 6);
	if (keycode == KEY_7)
		add_num(env, 7);
	if (keycode == KEY_8)
		add_num(env, 8);
	if (keycode == KEY_9)
		add_num(env, 9);
}

void		key_add(int keycode, t_env *env)
{
	if (keycode == KEY_NEG)
	{
		env->control->neg = env->control->neg == 1 ? -1 : 1;
		env->control->num = env->control->num * -1;
		if (env->control->num != 0)
			add_to_struct(env);
	}
	key_num(keycode, env);
}