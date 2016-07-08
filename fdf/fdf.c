#include "fdf.h"

static int		expose_hook(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

static int		key_hook(int keycode, t_env *env)
{
	if (keycode == 65307)
	{
		ft_memset(env->img->data, 0, env->img->width * env->img->height * env->img->opp);
		free(env->img);
		mlx_destroy_window(env->mlx, env->win);
		ft_arraykil(env->map, &ft_tabkil);
		ft_arraykil(env->gradient, &free);
		exit(0);
	}	
	return (0);
}

static t_image	*ft_new_image(t_env *env)
{
	t_image			*img;

	img = (t_image*)malloc(sizeof(t_image));
	img->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	img->data = (unsigned char*)mlx_get_data_addr(img->img, &img->opp, &img->l_size, &img->endian);
	printf("bpp : %d\n", img->opp);
	img->opp = img->opp / 8;
	printf("opp : %d\n", img->opp);
	printf("endian : %d\n", img->endian);
	img->width = WIDTH;
	img->height = HEIGHT;
	return (img);
}

static t_env	*env_init(void)
{
	t_env			*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error: malloc failed");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fil de fer");
	env->offset = PT(0, 0);
	env->img = ft_new_image(env);
	env->map = ft_arraynew();
	env->color = NULL;
	env->max_z = 0;
	env->min_z = 0;
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	return (env);
}

int				main(int argc, char **argv)
{
	int				fd;
	t_env			*env;

	if (argc <= 1)
		ft_error("Error: No file specified.\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error: File not found.\n");
	env = env_init();
	if (!ft_load_map(fd, env))
		ft_putstr_fd("Warning: File contains error.\n", 2);
	if (env->map->length <= 0)
		ft_error("Error: The file is too small.\n");
	ft_mapoffset(env);
	close(fd);
	env->color = ft_colornew(DEF_COLORS);
	ft_draw_map(env);
	mlx_loop(env->mlx);
	return (0);
}