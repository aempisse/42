#include "../rtv1.h"

int				key_hook(int keycode, t_env *env)
{
	keycode == KEY_ESC ? exit(0) : NULL;
	return (0);
}

int				key_menu(int keycode, t_env *env)
{

	keycode == KEY_ESC ? exit(0) : NULL;
	ft_putnbr(keycode);
	ft_putendl("");
	return (0);
}

int				loop_hook(t_env *env)
{
	int 		i;

	// if (env->render == 1)
	// 	mlx_put_image_to_window(env->mlx, env->win_menu, env->img_menu, 0, 0);
	if (env->render == 1)
	{
		i = 0;
		multi_threading(env);
		while (i < THREAD)
		{
			mlx_put_image_to_window(env->mlx, env->win_scene, env->img[i]->img, 0, (HEIGHT / THREAD) * i);
			i++;
		}
		
		env->render = 0;
	}
	return (0);
}
