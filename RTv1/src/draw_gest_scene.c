#include "../rtv1.h"

static void		draw_main_menu(t_env *env)
{
	int			color;

	mlx_string_put(env->mlx, env->win_control, 42, 25, 0xFFFFFFF, "Number of Object  : ");
	mlx_string_put(env->mlx, env->win_control, 250, 25, 0xFFF8C00, ft_itoa(env->sphere->length +
		env->plane->length + env->disk->length));
	mlx_string_put(env->mlx, env->win_control, 30, 50, 0xFFFFFFF, "Number of Spotlight : ");
	mlx_string_put(env->mlx, env->win_control, 250, 50, 0xFFF8C00, ft_itoa(env->control->nbr_sp));
	color = env->control->ctm_1 == 0 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 150, color, "See Object");
	color = env->control->ctm_1 == 1 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 200, color, "New Object");
	color = env->control->ctm_1 == 2 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 250, color, "Update Scene");
}

static void		draw_see_obj(t_env *env)
{
	mlx_string_put(env->mlx, env->win_control, 90, 25, 0xFFFFFFF, "List Object");
	mlx_string_put(env->mlx, env->win_control, 30, 100, 0xFFFFFFF, "See : ");
	mlx_string_put(env->mlx, env->win_control, 35, 150, 0xFFFFFFF, " Sphere : ");
	mlx_string_put(env->mlx, env->win_control, 145, 150, 0xFFFFFFF, ft_itoa(env->sphere->length));
	mlx_string_put(env->mlx, env->win_control, 155, 150, 0xFFFFFFF, " element(s).");
	mlx_string_put(env->mlx, env->win_control, 35, 175, 0xFFFFFFF, " Plane : ");
	mlx_string_put(env->mlx, env->win_control, 145, 175, 0xFFFFFFF, ft_itoa(env->plane->length));
	mlx_string_put(env->mlx, env->win_control, 155, 175, 0xFFFFFFF, " element(s).");
	mlx_string_put(env->mlx, env->win_control, 35, 200, 0xFFFFFFF, " Disk : ");
	mlx_string_put(env->mlx, env->win_control, 145, 200, 0xFFFFFFF, ft_itoa(env->disk->length));
	mlx_string_put(env->mlx, env->win_control, 155, 200, 0xFFFFFFF, " element(s).");
	ft_draw_small_arrow(env);
}

static void		draw_list_obj(t_env *env)
{
	draw_square(env);
	mlx_string_put(env->mlx, env->win_control, 90, 25, 0xFFFFFFF, "List Object");
	mlx_string_put(env->mlx, env->win_control, 75, 100, 0xFFFFFFF, "Element : ");
	mlx_string_put(env->mlx, env->win_control, 175, 100, 0xFFFFFFF, ft_itoa(env->control->i));
	mlx_string_put(env->mlx, env->win_control, 180, 100, 0xFFFFFFF, " / ");
	mlx_string_put(env->mlx, env->win_control, 80, 150, 0x0000000, "Type : ");
	mlx_string_put(env->mlx, env->win_control, 150, 150, 0x00000FF, env->control->name_obj);
	if (env->control->mod == 0)
		mlx_string_put(env->mlx, env->win_control, 90, 400, 0x7A4500, "'M' to Modify");
	else
		mlx_string_put(env->mlx, env->win_control, 60, 400, 0x7A4500, "'M' again to stop.");
	ft_draw_left_arrow(env);
	ft_draw_right_arrow(env);
	draw_value(env);
}

static void		draw_new_obj_value(t_env *env)
{
	if (ft_strcmp(env->control->name_obj, "Sphere") == 0 ||
		ft_strcmp(env->control->name_obj, "Disk") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Xc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Yc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Zc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 275, 0x0000000, "Radius : ");
		if (ft_strcmp(env->control->name_obj, "Sphere") == 0)
			draw_sphere_value(env);
		else
			draw_disk_value(env);
	}
	if (ft_strcmp(env->control->name_obj, "Plane") == 0)
	{
		mlx_string_put(env->mlx, env->win_control, 70, 200, 0x0000000, "Xc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 225, 0x0000000, "Yc : ");
		mlx_string_put(env->mlx, env->win_control, 70, 250, 0x0000000, "Zc : ");
		draw_plane_value(env);
	}
}

static void		draw_new_obj_add(t_env *env)
{
	draw_square(env);
	mlx_string_put(env->mlx, env->win_control, 100, 25, 0xFFFFFFF, "New Object");
	mlx_string_put(env->mlx, env->win_control, 80, 150, 0x0000000, "Type : ");
	mlx_string_put(env->mlx, env->win_control, 150, 150, 0x00000FF, env->control->name_obj);
	mlx_string_put(env->mlx, env->win_control, 60, 400, 0x7A4500, "'Enter' to valided.");
	draw_new_obj_value(env);
}

static void		draw_new_obj_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_control, 90, 25, 0xFFFFFFF, "New Object");
	mlx_string_put(env->mlx, env->win_control, 30, 100, 0xFFFFFFF, "Choose : ");
	mlx_string_put(env->mlx, env->win_control, 35, 150, 0xFFFFFFF, " Sphere");
	mlx_string_put(env->mlx, env->win_control, 35, 175, 0xFFFFFFF, " Plane");
	mlx_string_put(env->mlx, env->win_control, 35, 200, 0xFFFFFFF, " Disk");
	ft_draw_small_arrow(env);
}

void			draw_control(t_env *env)
{
	mlx_clear_window(env->mlx, env->win_control);
	if (env->control->menu == 0 || env->control->menu == 3)
		draw_main_menu(env);
	if (env->control->menu == 1)
		draw_see_obj(env);
	if (env->control->menu == 10)
		draw_list_obj(env);
	if (env->control->menu == 2)
		draw_new_obj_menu(env);
	if (env->control->menu == 20)
		draw_new_obj_add(env);
}