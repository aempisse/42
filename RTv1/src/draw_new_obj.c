#include "../rtv1.h"

static void		draw_new_obj_value_part2(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Xc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Yc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Zc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 275, 0x0000000, "Radius : ");
		draw_sphere_value(env);
	}
}

static void			draw_new_obj_value(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Pos x : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Pos y : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Pos z : ");
		mlx_string_put(env->mlx, env->win_control, 70, 275, 0x0000000, "Xn : ");
		mlx_string_put(env->mlx, env->win_control, 70, 300, 0x0000000, "Yn : ");
		mlx_string_put(env->mlx, env->win_control, 70, 325, 0x0000000, "Zn : ");
		draw_plane_value(env);
	}
	draw_new_obj_value_part2(env);
}

void			draw_new_obj_add(t_env *env)
{
	draw_square(env);
	mlx_string_put(env->mlx, env->win_control, 100, 25, 0xFFFFFFF, "New Object");
	mlx_string_put(env->mlx, env->win_control, 80, 150, 0x0000000, "Type : ");
	mlx_string_put(env->mlx, env->win_control, 150, 150, 0x00000FF, env->control->name_obj);
	mlx_string_put(env->mlx, env->win_control, 60, 400, 0x7A4500, "'Enter' to valided.");
	draw_new_obj_value(env);
}

void			draw_new_obj_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_control, 90, 25, 0xFFFFFFF, "New Object");
	mlx_string_put(env->mlx, env->win_control, 30, 100, 0xFFFFFFF, "Choose : ");
	mlx_string_put(env->mlx, env->win_control, 35, 150, 0xFFFFFFF, " Sphere");
	mlx_string_put(env->mlx, env->win_control, 35, 175, 0xFFFFFFF, " Plane");
	ft_draw_small_arrow(env);
}