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
	if (keycode == KEY_RIGHT && ft_strcmp(env->control->name_obj, "Disk") == 0 &&
 		env->control->i < env->disk->length - 1)
		env->control->i++;
	if (keycode == KEY_LEFT && ft_strcmp(env->control->name_obj, "Disk") == 0 &&
	 	env->control->i > 0)
		env->control->i--;
	return (0);
}

static void		incr_ctm(int keycode, t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
	{
		if (keycode == KEY_DOWN && env->control->ctm_1 < 2)
			env->control->ctm_1++;
		if (keycode == KEY_UP && env->control->ctm_1 > 0)
			env->control->ctm_1--;
	}
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0 ||
		ft_strcmp(env->control->name_obj, "Disk") == 0)
	{
		if (keycode == KEY_DOWN && env->control->ctm_1 < 3)
			env->control->ctm_1++;
		if (keycode == KEY_UP && env->control->ctm_1 > 0)
			env->control->ctm_1--;
	}
	env->control->neg = 1;
	env->control->num = 0;
	env->control->stop_add = 0; //
}

static void	add_num_plane(t_env *env)
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
}

static void	add_num_disk(t_env *env)
{
	t_sphere	*tmp;
	int			i;

	i = env->control->i;
	tmp = AG(t_disk*, env->disk, i);
	if (env->control->ctm_1 == 0)
		tmp->pos.x = env->control->num;
	if (env->control->ctm_1 == 1)
		tmp->pos.y = env->control->num;
	if (env->control->ctm_1 == 2)
		tmp->pos.z = env->control->num;
	if (env->control->ctm_1 == 3)
		tmp->radius = env->control->num;
}

static void	add_num_sphere(t_env *env)
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

static void	key_add(int keycode, t_env *env)
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

int				key_obj_menu(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
	{
		env->control->menu = 0;
		env->control->ctm_1 = 0;
	}
	if (keycode == KEY_DOWN && env->control->ctm_1 < 2)
		env->control->ctm_1++;
	if (keycode == KEY_UP && env->control->ctm_1 > 0)
		env->control->ctm_1--;
	if (keycode == KEY_ENTER)
	{
		env->control->menu = 10;
		env->control->name_obj = search_type_obj(env->control->ctm_1);
		env->control->ctm_1 = 0;
	}
	return (0);
}