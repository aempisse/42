#include "../rtv1.h"

int				expose_hook(t_env *env)
{
	draw_gest_scn(env);
	mlx_put_image_to_window(env->mlx, env->win_scn, env->img->img, 0, 0);
	return (0);
}

static int		key_menu_p(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 125 && env->gest->ctm_1 < 4)
		env->gest->ctm_1++;
	if (keycode == 126 && env->gest->ctm_1 > 0)
		env->gest->ctm_1--;
	if (keycode == 36)
	{
		if (env->gest->ctm_1 == 0)
			env->gest->menu = 1;
		if (env->gest->ctm_1 == 1)
			env->gest->menu = 2;
		if (env->gest->ctm_1 == 2)
			env->gest->menu = 3;
		if (env->gest->ctm_1 == 4)
			env->gest->menu = 5;
	}
	ft_putnbr(env->gest->menu);
	ft_putendl("");
	return (0);
}

static int		key_hook(int keycode, t_env *env)
{
	if (env->gest->menu == 0)
		key_menu_p(keycode, env);
	draw_gest_scn(env);
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
	env->win_scn = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	env->win_gest_scn = mlx_new_window(env->mlx, 300, 500, "Gestion Scene");
	env->img = ft_new_image(env->mlx);
	env->sphere = ft_array_new();
	env->plane = ft_array_new();
	mlx_expose_hook(env->win_scn, &expose_hook, env);
	mlx_key_hook(env->win_gest_scn, &key_hook, env);
	return (env);
}

static int 		nbr_of(t_env *env)
{
	int		i;
	int		nbr_o;

	i = 0;
	nbr_o = 0;
	while (i < env->sphere->length)
		i++;
	nbr_o = i;
	i = 0;
	while (i < env->plane->length)
		i++;
	nbr_o = nbr_o + i;
	return (nbr_o);
}

static t_gest	*gest_init(t_env *env)
{
	t_gest		*gest;
	if ((gest = (t_gest*)malloc(sizeof(t_gest))) == NULL)
		ft_error("Error : malloc() failed.\n");
	gest->ctm_1 = 0;
	gest->menu = 0;
	gest->nbr_o = nbr_of(env);
	gest->nbr_sp = 0; //gest->nbr_sp = env->spotlight->lenght;
	return (gest);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	t_gest		*gest;
	int			fd;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			ft_error("Error : File not found.\n");
		env = env_init();
		ft_load_file(fd, env);
		close(fd);
		env->gest = gest_init(env);
		ft_putstr("nombre obj : ");
		ft_putnbr(env->gest->nbr_o);
		ft_putendl("");
		/*
		** TEST DU PARSER
		*/
		int			i;
		t_sphere	*tmp;
		t_plane		*tmp2;

		printf("\nLa structure env->sphere contient %d elements.\n"
			, env->sphere->length);
		i = -1;
		while (++i < env->sphere->length)
		{
			tmp = AG(t_sphere*, env->sphere, i);
			printf("\nSphere %d\npos.x = %f\npos.y = %f\npos.z = %f\nradius = %f\n"
				, i, tmp->pos.x, tmp->pos.y, tmp->pos.z, tmp->radius);
		}
		printf("\nLa structure env->plane contient %d elements.\n"
			, env->plane->length);
		i = -1;
		while (++i < env->plane->length)
		{
			tmp2 = AG(t_plane*, env->plane, i);
			printf("\nPlane %d\npos.x = %f\npos.y = %f\npos.z = %f\n"
				, i, tmp2->pos.x, tmp2->pos.y, tmp2->pos.z);
		}
		/*
		** TEST DU PARSER
		*/
		mlx_loop(env->mlx);
	}
	return (0);
}