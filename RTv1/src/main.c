#include "../rtv1.h"

static t_env	*env_init(void)
{
	t_env		*env;
	int 		i;

	i = 0;
	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init() failed.\n");
	env->win_scene = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	while(i < THREAD)
		env->img[i++] = ft_new_image(env->mlx, WIDTH, HEIGHT, THREAD);
	env->nbr_obj = 0;
	env->scene = (t_scene*)malloc(sizeof(t_scene));
	env->scene->camera = (t_vector){(t_double3){0, 0, 0}, (t_double3){0, 0, 0}};
	env->scene->object = NULL;
	env->scene->light = NULL;
	env->scene->ambiant = 0.02;
	env->scene->aliaising = 0;
	env->scene->direct_light = 1;
	env->render = 1;
	mlx_key_hook(env->win_scene, &key_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

int				wrong_files(char const *str)
{
	int			i;
	int			j;
	char		*scn;

	i = 0;
	scn = ".scn";
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		j = 0;
		while (str[i] != '\0' && j <= 3)
		{
			if (str[i] != scn[j])
				return (0);
			i++;
			j++;
		}
	}
	else
		return (0);
	return (1);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	int			fd;

	if (argc != 2)
		ft_error("Error : Wrong numbers of Arguments.\n");
	if (wrong_files(argv[1]) != 1)
		ft_error("Error : File isn't a '.scn'\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	env = env_init();
	// init_menu(env);
	check_files(fd, env);
	print_object(&env->scene->object, &env->scene->light);
	close(fd);
	mlx_loop(env->mlx);
	return (0);
}
