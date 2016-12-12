#include "../rtv1.h"

static int		key_main_menu(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 125 && env->control->ctm_1 < 2)
		env->control->ctm_1++;
	if (keycode == 126 && env->control->ctm_1 > 0)
		env->control->ctm_1--;
	if (keycode == 36 && env->control->ctm_1 != 3)
	{
		env->control->menu = env->control->ctm_1 + 1;
		env->control->ctm_1 = 0;
	}
	if (keycode == 36 && env->control->ctm_1 == 3)
		env->render_scn = 1;
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

int				key_hook(int keycode, t_env *env)
{
	if (env->control->menu == 0 || env->control->menu == 3)
		key_main_menu(keycode, env);
	else if(env->control->menu == 1)
		key_obj_menu(keycode, env);
	else if (env->control->menu == 2)
		key_new_obj(keycode, env);
	else if (env->control->menu == 10)
		key_obj_in(keycode, env);
		draw_control(env);
	env->render = 1;
	//ft_putnbr(keycode);
	//ft_putendl("");
	return (0);
}