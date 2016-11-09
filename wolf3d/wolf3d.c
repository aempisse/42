#include "wolf3d.h"

static int		ft_load_line(t_env *env, t_tab *pts, t_buff *line)
{
	int			tmp;
	int			valid;

	valid = 1;
	ft_parse_space(line);
	while (line->data[line->i] != '\0')
	{
		tmp = ft_parse_int(line);
		ft_tab_add(pts, &tmp);
		if (line->data[line->i] != ' ' && line->data[line->i] != '\0')
			valid = 0;
		ft_parse_not(line, " \t\n");
		ft_parse_space(line);
	}
	return (valid);
}

int				ft_load_map(int fd, t_env *env)
{
	t_buff		line;
	t_tab		*tmp;
	int			valid;

	valid = 1;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_tab_new(sizeof(int));
		if (!ft_load_line(env, tmp, &line))
			valid = 0;
		ft_array_add(env->map, tmp);
	}
	return (valid);
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

t_env			*env_init(void)
{
	t_env		*env;

	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init() failed.\n");
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3d");
	env->img = ft_new_image(env->mlx);
	env->map = ft_array_new();
	env->pos = (t_vector){22, 12};
	env->dir = (t_vector){-1, 0};
	env->plane = (t_vector){0, 0.66};
	env->time = (t_vector){0, 0};
	env->render = 0;
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_key_hook(env->win, &key_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	int			fd;
	t_pt		block;
	t_tab		*tmp;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_error("Error : File not found.\n");
		env = env_init();
		if (!ft_load_map(fd, env))
			ft_putstr_fd("Warning : File contains errors.\n", 2);
		close(fd);
		block = (t_pt){0, -1};
		while (++block.y < env->map->length)
		{
			block.x = -1;
			tmp = (t_tab*)((t_array*)(env->map)->data[block.y]);
			while (++block.x < tmp->length)
			{
				ft_putnbr(TG(int, tmp, block.x));
				ft_putchar(' ');
			}
			ft_putchar('\n');
	}
		mlx_loop(env->mlx);
	}
	return 0;
}
