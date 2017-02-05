#include "../rtv1.h"

static void	draw_plane_second_part(t_env *env, t_plane *tmp, char *tmp_c)
{
	int		color;

	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 3 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.x);
	color = env->control->ctm_1 == 3 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 275, color, ft_itoa(tmp->normal.x));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 4 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.y);
	color = env->control->ctm_1 == 4 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 300, color, ft_itoa(tmp->normal.y));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 5 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.z);
	color = env->control->ctm_1 == 5 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 325, color, ft_itoa(tmp->normal.z));
}

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
	draw_plane_second_part(env, tmp, tmp_c);
}

static void	draw_disk_second_part(t_env *env, t_disk *tmp, char *tmp_c)
{
	int		color;

	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 4 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.y);
	color = env->control->ctm_1 == 4 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 300, color, ft_itoa(tmp->normal.y));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 5 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.z);
	color = env->control->ctm_1 == 5 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 325, color, ft_itoa(tmp->normal.z));
	if (env->control->mod == 1)
		tmp_c = env->control->ctm_1 == 6 ?
		ft_itoa(env->control->num) : ft_itoa(tmp->radius);
	color = env->control->ctm_1 == 6 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 350, color, ft_itoa(tmp->radius));
}

void		draw_disk_value(t_env *env)
{
	t_disk		*tmp;
	char		*tmp_c;
	int			color;

	tmp = AG(t_disk*, env->disk, env->control->i);
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
		ft_itoa(env->control->num) : ft_itoa(tmp->normal.x);
	color = env->control->ctm_1 == 3 ? 0x00000000 : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 170, 275, color, ft_itoa(tmp->normal.x));
	draw_disk_second_part(env, tmp, tmp_c);
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