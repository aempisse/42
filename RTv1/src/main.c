#include "../rtv1.h"

// j'ai remplacé le expose_hook par un loop_hook qui est appellé à chaque itération de mlx_loop
// j'utilise une variable env->render (render = afficher le rendu) pour savoir quand redessiner
// la fenêtre de contrôle
// on utilisera un truc similaire pour savoir quand redessiner la scene
int				loop_hook(t_env *env)
{
	if (env->render == 1)
	{
		draw_control(env);
		// mlx_put_image_to_window(env->mlx, env->win_scene, env->img->img, 0, 0);
		env->render = 0;
	}
	return (0);
}

static int		key_main_menu(int keycode, t_env *env)
{
	if (keycode == 125 && env->control->ctm_1 < 4)
		env->control->ctm_1++;
	if (keycode == 126 && env->control->ctm_1 > 0)
		env->control->ctm_1--;
	if (keycode == 36)
	{
		// if (env->control->ctm_1 == 0)
		// 	env->control->menu = 1;
		// if (env->control->ctm_1 == 1)
		// 	env->control->menu = 2;
		// if (env->control->ctm_1 == 2)
		// 	env->control->menu = 3;
		// if (env->control->ctm_1 == 4)
		// 	env->control->menu = 5;
		env->control->menu = env->control->ctm_1 + 1; // te prends pas la tete ^^
	}
	return (0);
}

static int		key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(0);
	if (env->control->menu == 0)
		key_main_menu(keycode, env);
	env->render = 1; // on a appuyé sur une touche, donc il faut redessiner la scène
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
	mlx_key_hook(env->win_control, &key_hook, env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

// static int 		nbr_of(t_env *env)
// {
// 	int		i;
// 	int		nbr_o;

// 	i = 0;
// 	nbr_o = 0;
// 	while (i < env->sphere->length)
// 		i++;
// 	nbr_o = i;
// 	i = 0;
// 	while (i < env->plane->length)
// 		i++;
// 	nbr_o = nbr_o + i;
// 	return (nbr_o);
// }

static void		*control_init(t_env *env)
{
	t_control		*control;

	if ((env->control = (t_control*)malloc(sizeof(t_control))) == NULL)
		ft_error("Error : malloc() failed.\n");
	env->control->ctm_1 = 0;
	env->control->menu = 0;
	// env->control->nbr_o = nbr_of(env);
	env->control->nbr_o = env->sphere->length + env->plane->length; // tout simplement ;)
	env->control->nbr_sp = 0; //control->nbr_sp = env->spotlight->lenght;
	// on peut meme supprimmer les deux variables nbr_o et nbr_sp et mettre directement
	// "env->sphere->length + env->plane->length" et "env->spotlight->length"
	// dans les itoa de la fonction draw_main_menu
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