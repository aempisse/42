#include "../rtv1.h"

void			ft_draw_right_arrow(t_env *env)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		mlx_pixel_put(env->mlx, env->win_control, 130, 450 + i, 0xFFF8C00);
		if (i < 16)
			mlx_pixel_put(env->mlx, env->win_control, 129, 451 + i, 0xFFF8C00);
		if (i < 14)
			mlx_pixel_put(env->mlx, env->win_control, 128, 452 + i, 0xFFF8C00);
		if (i < 12)
			mlx_pixel_put(env->mlx, env->win_control, 127, 453 + i, 0xFFF8C00);
		if (i < 10)
			mlx_pixel_put(env->mlx, env->win_control, 126, 454 + i, 0xFFF8C00);
		if (i < 8)
			mlx_pixel_put(env->mlx, env->win_control, 125, 455 + i, 0xFFF8C00);
		if (i < 6)
			mlx_pixel_put(env->mlx, env->win_control, 124, 456 + i, 0xFFF8C00);
		if (i < 4)
			mlx_pixel_put(env->mlx, env->win_control, 123, 457 + i, 0xFFF8C00);
		if (i < 2)
			mlx_pixel_put(env->mlx, env->win_control, 122, 458 + i, 0xFFF8C00);
		i++;
	}
}

void			ft_draw_left_arrow(t_env *env)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		mlx_pixel_put(env->mlx, env->win_control, 155, 450 + i, 0xFFF8C00);
		if (i < 16)
			mlx_pixel_put(env->mlx, env->win_control, 156, 451 + i, 0xFFF8C00);
		if (i < 14)
			mlx_pixel_put(env->mlx, env->win_control, 157, 452 + i, 0xFFF8C00);
		if (i < 12)
			mlx_pixel_put(env->mlx, env->win_control, 158, 453 + i, 0xFFF8C00);
		if (i < 10)
			mlx_pixel_put(env->mlx, env->win_control, 159, 454 + i, 0xFFF8C00);
		if (i < 8)
			mlx_pixel_put(env->mlx, env->win_control, 160, 455 + i, 0xFFF8C00);
		if (i < 6)
			mlx_pixel_put(env->mlx, env->win_control, 161, 456 + i, 0xFFF8C00);
		if (i < 4)
			mlx_pixel_put(env->mlx, env->win_control, 162, 457 + i, 0xFFF8C00);
		if (i < 2)
			mlx_pixel_put(env->mlx, env->win_control, 163, 458 + i, 0xFFF8C00);
		i++;
	}
}

void			ft_draw_small_arrow(t_env *env)
{
	int		y;
	int 	i;

	i = 0;
	if (env->control->ctm_1 == 0)
		y = 160;
	if (env->control->ctm_1 == 1)
		y = 185;
	if (env->control->ctm_1 == 2)
		y = 210;
	while (i < 10)
	{
		mlx_pixel_put(env->mlx, env->win_control, 27 + i, y, 0xFFF8C00);
		mlx_pixel_put(env->mlx, env->win_control, 27 + i++, y + 1, 0xFFF8C00);
	}
	i = 0;
	while (i < 6)
		mlx_pixel_put(env->mlx, env->win_control, 37, y - 2 + i++, 0xFFF8C00);
	i = 0;
	while (i < 4)
		mlx_pixel_put(env->mlx, env->win_control, 38, y - 1 + i++, 0xFFF8C00);
	i = 0;
	while (i < 2)
		mlx_pixel_put(env->mlx, env->win_control, 39, y + i++, 0xFFF8C00);
}

void			draw_square(t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 300)
	{
		while (j < 200)
		{
			mlx_pixel_put(env->mlx, env->win_control, 50 + j, 140 + i, 0xFFFFFFF);
			j++;
		}
		j = 0;
		i++;
	}
}