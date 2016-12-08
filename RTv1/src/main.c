#include "../rtv1.h"

// static t_image	*ft_new_image(void *mlx)
// {
// 	t_image		*img;

// 	if ((img = (t_image*)malloc(sizeof(t_image))) == NULL)
// 		ft_error("Error: malloc failed.\n");
// 	img->img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	img->data = (unsigned char*)mlx_get_data_addr(img->img, &img->opp, 
// 		&img->l_size, &img->endian);
// 	img->opp = img->opp / 8;
// 	img->width = WIDTH;
// 	img->height = HEIGHT;
// 	return (img);
// }

static t_env	*env_init()
{
	t_env		*env;
	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	// if ((env->mlx = mlx_init()) == NULL)
	// 	ft_error("Error : mlx_init() failed.\n");
	// env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	// env->img = ft_new_image(env->mlx);
	env->sphere = ft_array_new();
	env->plane = ft_array_new();
	/*
	**hooks
	*/
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
		/*
		** TEST DU PARSER
		*/
		int			i = -1;
		t_plane		*tmp;

		printf("La structure env->plane contient %d elements.\n"
			, env->plane->length);
		while (++i < env->plane->length)
		{
			tmp = AG(t_plane*, env->plane, i);
			printf("\nPlane %d\npos.x = %f\npos.y = %f\npos.z = %f\n" , i, tmp->pos.x, tmp->pos.y, tmp->pos.z);
		}
		/*
		** TEST DU PARSER
		*/
		// mlx_loop(env->mlx);
	}
	else
		ft_error("Error : Wrong number of argument.\n");
	return (0);
}