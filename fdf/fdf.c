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
		ft_memset(env->img->data, 0, env->img->width * env->img->height * 
			env->img->opp);
		free(env->img);
		mlx_destroy_window(env->mlx, env->win);
		ft_array_kill(env->map, &ft_tab_kill);
		ft_array_kill(env->color, &free);
		exit(0);
	}	
	return (0);
}

static t_image	*ft_new_image(t_env *env)
{
	t_image		*img;

	if ((img = (t_image*)malloc(sizeof(t_image))) == NULL)
		ft_error("Error: malloc failed.\n");
	img->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	img->data = (unsigned char*)mlx_get_data_addr(img->img, &img->opp, 
		&img->l_size, &img->endian);
	img->opp = img->opp / 8;
	img->width = WIDTH;
	img->height = HEIGHT;
	return (img);
}

static t_env	*env_ini(void)
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error: malloc failed.\n");
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Fil de fer");
	env->offset = PT(0, 0);
	env->img = ft_new_image(env);
	env->map = ft_array_new();
	env->color = NULL;
	env->max_z = 0;
	env->min_z = 0;
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	return (env);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_env		*env;

	if (argc <= 1)
		ft_error("Error: No file specified.\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error: File not found.\n");
	env = env_ini();
	if (!ft_load_map(fd, env))
		ft_putstr_fd("Warning: File contains error.\n", 2);
	if (env->map->length <= 0)
		ft_error("Error: The file is too small.\n");
	ft_map_offset(env);
	close(fd);
	env->color = (argc > 2 ? ft_new_color(argv[2]) : ft_new_color(DEF_COLORS));
	ft_draw_map(env);
	mlx_loop(env->mlx);
	return (0);
}