#include "../rtv1.h"

static void		draw_menu_p(t_env *env)
{
	mlx_string_put(env->mlx, env->win_gest_scn, 42, 25, 0xFFFFFFF, "Number of Object  : ");
	mlx_string_put(env->mlx, env->win_gest_scn, 250, 25, 0xFFF8C00, ft_itoa(env->gest->nbr_o));
	mlx_string_put(env->mlx, env->win_gest_scn, 30, 50, 0xFFFFFFF, "Number of Spotlight : ");
	mlx_string_put(env->mlx, env->win_gest_scn, 250, 50, 0xFFF8C00, ft_itoa(env->gest->nbr_sp));
	ft_putnbr(env->gest->ctm_1);
	ft_putendl("");
	if (env->gest->ctm_1 == 0)
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 150, 0xFFFFFFF, "See Object");
	else
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 150, 0xFFF8C00, "See Object");
	if (env->gest->ctm_1 == 1)
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 200, 0xFFFFFFF, "See Spotlight");
	else
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 200, 0xFFF8C00, "See Spotlight");
	if (env->gest->ctm_1 == 2)
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 250, 0xFFFFFFF, "Modify Object");
	else
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 250, 0xFFF8C00, "Modify Object");
	if (env->gest->ctm_1 == 3)
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 300, 0xFFFFFFF, "New Object");
	else
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 300, 0xFFF8C00, "New Object");
	if (env->gest->ctm_1 == 4)
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 350, 0xFFFFFFF, "Update Scene");
	else
		mlx_string_put(env->mlx, env->win_gest_scn, 70, 350, 0xFFF8C00, "Update Scene");
}

void			draw_gest_scn(t_env *env)
{
	if (env->gest->menu == 0)
		draw_menu_p(env);
}