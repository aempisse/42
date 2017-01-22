#include "../rtv1.h"

int				loop_hook(t_env *env)
{
	draw_control(env);
	if (env->render == 1)
	{
		render(env);
		mlx_put_image_to_window(env->mlx, env->win_scene, env->img->img, 0, 0);
		env->render = 0;
	}
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

static t_env	*env_init()
{
	t_env		*env;
	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init() failed.\n");
	env->win_scene = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	env->win_control = mlx_new_window(env->mlx, 300, 500, "control");	
	env->img = ft_new_image(env->mlx);
	env->sphere = ft_array_new();
	env->plane = ft_array_new();
	env->disk = ft_array_new();
	env->camera = (t_camera){(t_double3){0, 0, 0}, (t_double3){0, 0, -1}};
	env->fov = FOV;
	env->render = 1;
	mlx_key_hook(env->win_control, &key_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

static void		*control_init(t_env *env)
{
	t_control		*control;

	if ((env->control = (t_control*)malloc(sizeof(t_control))) == NULL)
		ft_error("Error : malloc() failed.\n");
	env->control->ctm_1 = 0;
	env->control->menu = 0;
	env->control->nbr_sp = 0;
	env->control->i = 0;
	env->control->mod = 0;
	env->control->num = 0;
	env->control->neg = 1;
	env->control->stop_add = 0;
	return (control);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	int			fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_error("Error : File not found.\n");
		env = env_init();
		ft_load_file(fd, env);
		close(fd);
		control_init(env);
		mlx_loop(env->mlx);
	}
	return (0);
}