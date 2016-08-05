#include "fractol.h"

int			expose_hook(t_env *env)
{
	ft_mandelbrot(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

int			key_hook(int keycode, t_env *env)
{
//	printf("%d\n", keycode);
	if (keycode == 65307)
	{
		ft_memset(env->img->data, 0, env->img->width * env->img->height * 
			env->img->opp);
		free(env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	else if (keycode == 65361)
		env->offset.x -= 50;
	else if (keycode == 65363)
		env->offset.x += 50;
	else if (keycode == 65362)
		env->offset.y -= 50;
	else if (keycode == 65364)
		env->offset.y += 50;
	else if (keycode == 65365)
		env->loop += 5;
	else if (keycode == 65366)
		env->loop -= 5;
	else if (keycode == 'c')
		ft_switch_color(env);
	else
		return(0);
	env->rerender = 1;
	return (0);
}

int			mouse_hook(int button, int x, int y, t_env *env)
{
	t_complex	pos;


//	printf("mouse button : %d\nx position : %d\ny position : %d\n", button, x, y);
	if (button == 1 || (button == 3 && env->zoom > 100))
	{
		pos.r = (env->offset.x + x) / env->zoom;
		pos.i = (env->offset.y + y) / env->zoom;
		env->zoom *= button == 1 ?  1.1 : 0.9;
		env->offset.x = pos.r * env->zoom - (WIDTH / 2);
		env->offset.y = pos.i * env->zoom - (HEIGHT / 2);
	}
	env->rerender = 1;
	return (0);
}

int			loop_hook(t_env *env)
{
	if (env->rerender == 1)
	{
		expose_hook(env);
		env->rerender = 0;
	}
	return (0);
}
