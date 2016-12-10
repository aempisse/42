#include "../rtv1.h"

static void		draw_main_menu(t_env *env)
{
	int			color;

	mlx_string_put(env->mlx, env->win_control, 42, 25, 0xFFFFFFF, "Number of Object  : ");
	mlx_string_put(env->mlx, env->win_control, 250, 25, 0xFFF8C00, ft_itoa(env->sphere->length + env->plane->length));
	mlx_string_put(env->mlx, env->win_control, 30, 50, 0xFFFFFFF, "Number of Spotlight : ");
	mlx_string_put(env->mlx, env->win_control, 250, 50, 0xFFF8C00, ft_itoa(env->control->nbr_sp));
	color = env->control->ctm_1 == 0 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 150, color, "See Object");
	color = env->control->ctm_1 == 1 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 200, color, "See Spotlight");
	color = env->control->ctm_1 == 2 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 250, color, "New Object");
	color = env->control->ctm_1 == 3 ? 0xFFFFFFF : 0xFFF8C00;
	mlx_string_put(env->mlx, env->win_control, 70, 300, color, "Update Scene");
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
	ft_draw_left_arrow(env);
	ft_draw_right_arrow(env);
	//draw_value(env);
}

void			draw_control(t_env *env)
{
	mlx_clear_window(env->mlx, env->win_control);
	if (env->control->menu == 0 || env->control->menu == 4)
		draw_main_menu(env);
	if (env->control->menu == 1)
		draw_see_obj(env);
	if (env->control->menu == 10)
		draw_list_obj(env);
	if (env->control->menu == 2)
		ft_putendl("Menu 'See Spotlight'.");
	if (env->control->menu == 3)
		ft_putendl("Menu 'New Object'.");
}