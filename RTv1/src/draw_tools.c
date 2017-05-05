#include "../rtv1.h"

void			ft_draw_right_arrow(t_env *env)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		mlx_pixel_put(env->mlx, env->win_menu, 120, 520 + i, 0xF00D532);
		if (i < 16)
			mlx_pixel_put(env->mlx, env->win_menu, 119, 521 + i, 0xF00D532);
		if (i < 14)
			mlx_pixel_put(env->mlx, env->win_menu, 118, 522 + i, 0xF00D532);
		if (i < 12)
			mlx_pixel_put(env->mlx, env->win_menu, 117, 523 + i, 0xF00D532);
		if (i < 10)
			mlx_pixel_put(env->mlx, env->win_menu, 116, 524 + i, 0xF00D532);
		if (i < 8)
			mlx_pixel_put(env->mlx, env->win_menu, 115, 525 + i, 0xF00D532);
		if (i < 6)
			mlx_pixel_put(env->mlx, env->win_menu, 114, 526 + i, 0xF00D532);
		if (i < 4)
			mlx_pixel_put(env->mlx, env->win_menu, 113, 527 + i, 0xF00D532);
		if (i < 2)
			mlx_pixel_put(env->mlx, env->win_menu, 112, 528 + i, 0xF00D532);
		i++;
	}
}
void			ft_draw_left_arrow(t_env *env)
{
	int		i;
	
	i = 0;
	while (i < 18)
	{
		mlx_pixel_put(env->mlx, env->win_menu, 365, 520 + i, 0xF00D532);
		if (i < 16)
			mlx_pixel_put(env->mlx, env->win_menu, 366, 521 + i, 0xF00D532);
		if (i < 14)
			mlx_pixel_put(env->mlx, env->win_menu, 367, 522 + i, 0xF00D532);
		if (i < 12)
			mlx_pixel_put(env->mlx, env->win_menu, 368, 523 + i, 0xF00D532);
		if (i < 10)
			mlx_pixel_put(env->mlx, env->win_menu, 369, 524 + i, 0xF00D532);
		if (i < 8)
			mlx_pixel_put(env->mlx, env->win_menu, 370, 525 + i, 0xF00D532);
		if (i < 6)
			mlx_pixel_put(env->mlx, env->win_menu, 371, 526 + i, 0xF00D532);
		if (i < 4)
			mlx_pixel_put(env->mlx, env->win_menu, 372, 527 + i, 0xF00D532);
		if (i < 2)
			mlx_pixel_put(env->mlx, env->win_menu, 373, 528 + i, 0xF00D532);
		i++;
	}
}