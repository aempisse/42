#include "../rtv1.h"

static int		key_main_menu(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 125 && env->control->ctm_1 < 3)
		env->control->ctm_1++;
	if (keycode == 126 && env->control->ctm_1 > 0)
		env->control->ctm_1--;
	if (keycode == 36 && env->control->ctm_1 != 4)
	{
		env->control->menu = env->control->ctm_1 + 1;
		env->control->ctm_1 = 0;
	}
	if (keycode == 36 && env->control->ctm_1 == 4)
		env->render_scn = 1;
	return (0);
}

static char		*search_type_obj(int c)
{
	char	*str;

	if (c == 0)
		str = "Sphere";
	if (c == 1)
		str = "Plane";
	return (str);
}

static int		key_sp_menu(int keycode, t_env *env)
{
	if (keycode == 53)
	{
		env->control->menu = 0;
		env->control->ctm_1 = 0;
	}
	return (0);
}

static int		key_new_obj(int keycode, t_env *env)
{
	if (keycode == 53)
	{
		env->control->menu = 0;
		env->control->ctm_1 = 0;
	}
	return (0);
}

static int		key_obj_in(int keycode, t_env *env)
{
	if (keycode == 53)
	{
		env->control->menu = 1;
		env->control->ctm_1 = 0;
	}
	return (0);
}

static int		key_obj_menu(int keycode, t_env *env)
{
	if (keycode == 53)
	{
		env->control->menu = 0;
		env->control->ctm_1 = 0;
	}
	if (keycode == 125 && env->control->ctm_1 < 1)
		env->control->ctm_1++;
	if (keycode == 126 && env->control->ctm_1 > 0)
		env->control->ctm_1--;
	if (keycode == 36)
	{
		env->control->menu = 10;
		env->control->name_obj = search_type_obj(env->control->ctm_1);
		env->control->ctm_1 = 0;
	}
	return (0);
}

int				key_hook(int keycode, t_env *env)
{
	if (env->control->menu == 0 || env->control->menu == 4)
		key_main_menu(keycode, env);
	else if (env->control->menu == 1)
		key_obj_menu(keycode, env);
	else if (env->control->menu == 2)
		key_sp_menu(keycode, env);
	else if (env->control->menu == 3)
		key_new_obj(keycode, env);
	else if (env->control->menu == 10)
		key_obj_in(keycode, env);
	env->render = 1;
	return (0);
}