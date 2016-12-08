#include "../wolf3d.h"

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

t_env			*env_init(void)
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init() failed.\n");
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
	env->win2 = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3dbis");
	env->img = ft_new_image(env->mlx);
	env->map = (int**)malloc(sizeof(int*) * MAP_HEIGHT);
	env->pos = (t_vector){8.5, 6.5};
	env->dir = (t_vector){0, -1};
	env->plane = (t_vector){0.66, 0};
	env->key = (t_key){0, 0, 0, 0};
	env->state = 0;
	env->render = 1;
	env->old_time = 0;
	env->new_time = 0;
	env->color_id = 0;
	env->color = &color0;
	// mlx_expose_hook(env->win, &expose_hook, env);
	// mlx_key_hook(env->win, &key_hook, env);
	mlx_hook(env->win, KEY_PRESS, KEY_PRESS_MASK, &key_press, env);
	mlx_hook(env->win, KEY_RELEASE, KEY_RELEASE_MASK, &key_release, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	int			fd;
	t_pt		block;
	// t_tab		*tmp;

	if (argc == 1)
	{
		if ((fd = open("map.wolf", O_RDONLY)) < 0)
			ft_error("Error : File not found.\n");
		env = env_init();
		if (!ft_load_map(fd, env))
			ft_putstr_fd("Warning : File contains errors.\n", 2);
		close(fd);
		// block = (t_pt){0, -1};
		// while (++block.y < env->map->length)
		// {
		// 	block.x = -1;
		// 	tmp = (t_tab*)((t_array*)(env->map)->data[block.y]);
		// 	while (++block.x < tmp->length)
		// 	{
		// 		ft_putnbr(TG(int, tmp, block.x));
		// 		ft_putchar(' ');
		// 	}
		// 	ft_putchar('\n');
		// }
		block = (t_pt){0, -1};
		while (++block.y < MAP_HEIGHT)
		{
			block.x = -1;
			while (++block.x < MAP_WIDTH)
			{
				ft_putnbr(env->map[block.y][block.x]);
				ft_putchar(' ');
			}
			ft_putchar('\n');
		}
		mlx_loop(env->mlx);
	}
	return 0;
}
