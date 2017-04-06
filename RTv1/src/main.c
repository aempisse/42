#include "../rtv1.h"

int				key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int				loop_hook(t_env *env)
{
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
	env->img = ft_new_image(env->mlx);
	if ((env->objects = (t_objects*)malloc(sizeof(t_objects))) == NULL)
		ft_error("Error : malloc() failed.\n");
	env->objects->spheres = ft_array_new();
	env->objects->planes = ft_array_new();
	env->objects->cylinders = ft_array_new();
	env->objects->cones = ft_array_new();
	env->objects->lights = ft_array_new();
	env->camera = (t_vector){(t_double3){0, 0, 0}, (t_double3){0, 0, 0}};
	env->render = 1;
	mlx_key_hook(env->win_scene, &key_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
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

		// int 		i = -1;
		// t_cone	*tmp;
		// while (++i < env->objects->cones->length)
		// {
		// 	tmp = AG(t_cone*, env->objects->cones, i);
		// 	printf("pos : %.0f %.0f %.0f\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		// 	printf("nor : %.0f %.0f %.0f\n", tmp->normal.x, tmp->normal.y, tmp->normal.z);
		// 	printf("ape : %.0f\n", tmp->aperture);
		// 	printf("col : %.0f %.0f %.0f\n", tmp->color.x, tmp->color.y, tmp->color.z);
		// 	printf("ior : %.0f\n", tmp->ior);
		// 	printf("mat : %d\n", tmp->material);
		// }

		mlx_loop(env->mlx);
	}
	return (0);
}