#include "../rtv1.h"

static void		refresh(t_env *env)
{
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(env->menu->path, O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	env->scene->object = NULL;
	env->scene->light = NULL;
	check_files(fd, env);
	while(i < THREAD)
	{
		ft_bzero(env->img[i]->data, env->img[i]->l_size);
		i++;
	}
	env->menu->render = 1;
	mlx_string_put(((t_env*)env)->mlx, ((t_env*)env)->win_scene, 100, 100, 0xF00D532, "Loading...");
}

static void		change_scene(t_env *env)
{
	int 			i;

	i = 0;
	while(env->menu->tab_scn[i] != NULL)
	{
		if (i == env->menu->index + (env->menu->i_page * 5))
		{
			env->menu->path = (char*)malloc(sizeof(char) * (strlen("scenes/") + strlen(env->menu->tab_scn[i])));
			env->menu->path = ft_strcat(ft_strcat(env->menu->path, "scenes/"), env->menu->tab_scn[i]);
		}
		i++;
	}
}

static void		key_enter_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
	{
		env->menu->index == 0 ? refresh(env) : 0;
		env->menu->index == 2 ? save_img(env) : 0;
		if (env->menu->index == 1)
		{
			env->menu->menu_lvl = 1;
			env->menu->index = 0;
			env->menu->i_page = 0;
		}
		else if (env->menu->index == 2)
			save_img(env);
	}
	else if (env->menu->menu_lvl == 1)
	{
		change_scene(env);
		env->menu->menu_lvl = 0;
		env->menu->index = 0;
	}
}

static void		key_UpDown_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 0)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
		else if (keycode == D_ARROW && env->menu->index < 2)
			env->menu->index++;
	}
	else if (env->menu->menu_lvl == 1)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
		else if (keycode == D_ARROW && env->menu->i_page == env->menu->page_max)
		{
			if (env->menu->index < (env->menu->page_max * 5) - env->menu->nbr_scn)
				env->menu->index++;
		}
		else if (keycode == D_ARROW && env->menu->index < 4)
			env->menu->index++;
	}
}

static void		key_esc_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		exit (0);
	else if (env->menu->menu_lvl == 1 || env->menu->menu_lvl == 2)
		env->menu->menu_lvl = 0;
	env->menu->index = 0;
}

static void		key_LeftRight_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 1)
	{
		if (keycode == R_ARROW && env->menu->i_page < env->menu->page_max)
		{
			env->menu->i_page++;
			env->menu->index = 0;
		}
		else if (keycode == L_ARROW && env->menu->i_page > 0)
		{
			env->menu->i_page--;
			env->menu->index = 0;
		}
	}
}

int				key_hook(int keycode, t_env *env)
{
	// printf("%i\n", keycode);
	if (keycode == KEY_ESC)
		key_esc_menu(env);
	if (keycode == KEY_ENTER)
		key_enter_menu(env);
	if (keycode == U_ARROW || keycode == D_ARROW)
		key_UpDown_menu(env, keycode);
	if (keycode == L_ARROW || keycode == R_ARROW)
		key_LeftRight_menu(env, keycode);
	return (0);
}

void			*wait_draw(void *env)
{
	mlx_string_put(((t_env*)env)->mlx, ((t_env*)env)->win_scene, 100, 100, 0xF00D532, ((t_env*)env)->win_scene);
    pthread_exit(0);
}

int				loop_hook(t_env *env)
{
	int 		i;
	pthread_t   th;

	if (env->menu->render == 1)
	{
		mlx_clear_window(env->mlx, env->win_scene);
		if (pthread_create(&th, NULL, wait_draw, env) != 0)
            ft_error("Thread create went wrong.");
		i = 0;
		multi_threading(env);
		pthread_join(th, NULL);
		while (i < THREAD)
		{
			mlx_put_image_to_window(env->mlx, env->win_scene, env->img[i]->img, 0, (HEIGHT / THREAD) * i);
			i++;
		}
		env->menu->render = 0;
	}
	mlx_clear_window(env->mlx, env->win_menu);
	mlx_put_image_to_window(env->mlx, env->win_menu, env->menu->img->img, 0, 0);
	draw_menu(env);
	return (0);
}
