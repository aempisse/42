#include "../rtv1.h"

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
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Pos x : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Pos y : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Pos z : ");
		mlx_string_put(env->mlx, env->win_control, 70, 275, 0x0000000, "Xn : ");
		mlx_string_put(env->mlx, env->win_control, 70, 300, 0x0000000, "Yn : ");
		mlx_string_put(env->mlx, env->win_control, 70, 325, 0x0000000, "Zn : ");
		mlx_string_put(env->mlx, env->win_control, 205, 100, 0xFFFFFFF, ft_itoa(env->plane->length - 1));
		draw_plane_value(env);
	}
}