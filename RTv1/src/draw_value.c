#include "../rtv1.h"

void		draw_plane_value(t_env *env)
{
	t_plane		*tmp;
	char		*tmp_c;
	int			color;

	tmp = AG(t_plane*, env->plane, env->control->i);
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 0 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.x);
	color = env->control->ctm_1 == 0 ? 0x0000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 200, color, ft_itoa(tmp->pos.x));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 1 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.y);
	color = env->control->ctm_1 == 1 ? 0x0000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 225, color, ft_itoa(tmp->pos.y));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 2 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.z);
	color = env->control->ctm_1 == 2 ? 0x0000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 250, color, ft_itoa(tmp->pos.z));
}

void		draw_sphere_value(t_env *env)
{
	t_sphere	*tmp;
	char		*tmp_c;
	int			color;

	tmp = AG(t_sphere*, env->sphere, env->control->i);
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 0 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.x);
	color = env->control->ctm_1 == 0 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 200, color, ft_itoa(tmp->pos.x));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 1 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.y);
	color = env->control->ctm_1 == 1 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 225, color, ft_itoa(tmp->pos.y));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 2 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->pos.z);
	color = env->control->ctm_1 == 2 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 250, color, ft_itoa(tmp->pos.z));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 3 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->radius);
	color = env->control->ctm_1 == 3 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 275, color, ft_itoa(tmp->radius));
}

void			draw_value(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Xc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Yc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Zc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 275, 0x0000000, "Radius : ");
		mlx_string_put(env->mlx, env->win_control, 205, 100, 0xFFFFFFF, ft_itoa(env->sphere->length - 1));
		draw_sphere_value(env);
	}
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Xc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Yc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Zc : ");
		mlx_string_put(env->mlx, env->win_control, 205, 100, 0xFFFFFFF, ft_itoa(env->plane->length - 1));
		draw_plane_value(env);
	}
}