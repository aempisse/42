#include "fractol.h"

static int		expose_hook(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

static int		key_hook(int keycode, t_env *env)
{
	printf("key pressed : %d\n", keycode);
	if (keycode == 65307)
	{
		ft_memset(env->img->data, 0, env->img->width * env->img->height * 
			env->img->opp);
		free(env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}	
	return (0);
}

static int		mouse_hook(int button, int x, int y, t_env *env)
{
	if (env->mlx)
		printf("mouse button : %d\nx position : %d\ny position : %d\n", button, x, y);
	return (0);
}

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

static t_env			*env_init()
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init failed\n");
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fract'ol");
	env->img = ft_new_image(env->mlx);
	mlx_expose_hook(env->mlx, &expose_hook, env);
	mlx_key_hook(env->mlx, &key_hook, env);
	mlx_mouse_hook(env->mlx, &mouse_hook, env);
	return (env);
}

int				main(void)
{
	t_env		*env;

	env = env_init();
	mlx_loop(env->mlx);
	return (0);
}