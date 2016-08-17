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

static void		ft_select_fractal(t_env *env, char *input)
{
	if (!ft_strcmp(input, "mandelbrot"))
	{
		env->start_pos = (t_lpt){-(2 * WIDTH / 3), -(HEIGHT / 2)};
		env->draw = &ft_mandelbrot;
	}
	else if (!ft_strcmp(input, "julia"))
	{
		env->start_pos = (t_lpt){-(WIDTH / 2), -(HEIGHT / 2)};
		env->draw = &ft_julia;
	}
	else
		ft_error("Error : wrong argument.\n");
}

static t_env			*env_init(char *input)
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc failed.\n");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fract_ol");
	env->img = ft_new_image(env->mlx);
	ft_select_fractal(env, input);
	env->offset = (t_lpt){env->start_pos.x, env->start_pos.y};
	env->zoom = 200;
	env->zoom_offset = 0;
	env->renderer = 0;
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

int				main(int argc, char **argv)
{
	t_env		*env;

	if (argc != 2)
		ft_error("Error : wrong number of arguments.\n");
	else
	{
		env = env_init(argv[1]);
		mlx_loop(env->mlx);
	}
	return (0);
}
