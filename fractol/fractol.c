#include "fractol.h"

static t_image	*ft_new_image(void *mlx)
{
	t_image		*img;

	if ((img = (t_image*)malloc(sizeof(t_image))) == NULL)
		ft_error("Error: malloc failed.\n");
	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->data = (unsigned char*)mlx_get_data_addr(img->img, &img->opp, 
		&img->l_size, &img->endian);
	img->opp = img->opp / 8;
	img->width = WIDTH;
	img->height = HEIGHT;
	return (img);
}

static t_env			*env_init(void)
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc failed.\n");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fract_ol");
	env->img = ft_new_image(env->mlx);
	env->offset = (t_lpt){-(WIDTH / 2), -(HEIGHT / 2)}; //mandelbrot {-420, -300} julia {WIDTH / 2, HEIGHT / 2}
	env->zoom = 200;
	env->zoom_offset = 0;
	env->rerender = 0;
	env->color_id = 0;
	env->color = &ft_color0;
	env->loop = LOOP;
	env->zoom_toggle = 0;
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_mouse_hook(env->win, &mouse_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

int				main(void)
{
	t_env		*env;

	env = env_init();
	mlx_loop(env->mlx);
	return (0);
}