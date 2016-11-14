#include "../wolf3d.h"

int				expose_hook(t_env *env)
{
	raycasting(env);
	minimap(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

void			rotate_vect(t_env *env, double rot_speed)
{
	double			old_dir_x;
	double			old_plane_x;

	old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(rot_speed) - env->dir.y * sin(rot_speed);
		env->dir.y = old_dir_x * sin(rot_speed) + env->dir.y * cos(rot_speed);
	old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(rot_speed) - env->plane.y * sin(rot_speed);
		env->plane.y = old_plane_x * sin(rot_speed) + env->plane.y * cos(rot_speed);
}

void			translate_vect(t_env *env, double move_speed)
{
	if (env->map[(int)(env->pos.x + env->dir.x * move_speed)]
		[(int)env->pos.y] == 0)
	// if (TG(int, AG(t_tab*, env->map, (int)env->pos.y),
	// 	(int)(env->pos.x + env->dir.x * move_speed)) == 0)
		env->pos.x += env->dir.x * move_speed;
	if (env->map[(int)env->pos.x]
		[(int)(env->pos.y + env->dir.y * move_speed)] == 0)
	// if (TG(int, AG(t_tab*, env->map, (int)(env->pos.y + env->dir.y * move_speed)),
	// 	(int)(env->pos.x)) == 0)
		env->pos.y += env->dir.y * move_speed;
}

int				key_press(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == 'c')
		switch_color(env);
	// if (keycode == 32)
	// {
	// 	env->state = (env->state + 1) % 5;
	// 	if (env->state >= 3)
	// 		mlx_do_key_autorepeaton(env->mlx);
	// 	else
	// 		mlx_do_key_autorepeatoff(env->mlx);
	// }
	if (keycode == KEY_LEFT && (env->state == 2 || env->state == 3))
		rotate_vect(env, HALF_PI);
	if (keycode == KEY_RIGHT && (env->state == 2 || env->state == 3))
		rotate_vect(env, -HALF_PI);
	if (keycode == KEY_UP && (env->state <= 2))
		translate_vect(env, 1);
	if (keycode == KEY_DOWN && (env->state == 1 || env->state == 2))
		translate_vect(env, -1);
	if (keycode == KEY_LEFT && env->state == 4)
		env->key.left = 1;	
	if (keycode == KEY_RIGHT && env->state == 4)
		env->key.right = 1;
	if (keycode == KEY_UP && (env->state == 3 || env->state == 4))
		env->key.up = 1;
	if (keycode == KEY_DOWN && (env->state == 3 || env->state == 4))
		env->key.down = 1;
	env->render = 1;
	return (0);
}

int				key_release(int keycode, t_env *env)
{
	if (keycode == KEY_LEFT)
		env->key.left = 0;
	if (keycode == KEY_RIGHT)
		env->key.right = 0;
	if (keycode == KEY_UP)
		env->key.up = 0;
	if (keycode == KEY_DOWN)
		env->key.down = 0;
	env->render = 1;
	return (0);
}

int				loop_hook(t_env *env)
{
	double		frametime;

	env->old_time = env->new_time;
	env->new_time = clock();
	frametime = (env->new_time - env->old_time) / (double)CLOCKS_PER_SEC;
	if (env->key.up == 1)
		translate_vect(env, MOVE_SPEED * frametime);
	if (env->key.down == 1)
		translate_vect(env, -MOVE_SPEED * frametime);
	if (env->key.left == 1)
		rotate_vect(env, ROT_SPEED * frametime);
	if (env->key.right == 1)
		rotate_vect(env, -ROT_SPEED * frametime);
	if (env->render == 1)
	{
		raycasting(env);
		change_state(env);
		minimap(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
		unlocked_messages(env);
		// printf("\npos.x = %f\npos.y = %f", env->pos.x, env->pos.y);
		// printf("\ndir.x = %f\ndir.y = %f", env->dir.x, env->dir.y);
		// printf("\n(int)pos.x = %d\n(int)pos.y = %d", (int)env->pos.x, (int)env->pos.y);
		// printf("\n");
		env->render = 0;
	}
	return (0);
}

void			unlocked_messages(t_env *env)
{
	mlx_string_put(env->mlx, env->win, 50, 400, 0x00FF0000, "UNLOCKED MOVE UP");
	if (env->state >= 1)
		mlx_string_put(env->mlx, env->win, 50, 420, 0x00FF0000, "UNLOCKED MOVE DOWN");
	if (env->state >= 2)
	{
		mlx_string_put(env->mlx, env->win, 50, 440, 0x00FF0000, "UNLOCKED MOVE LEFT");
		mlx_string_put(env->mlx, env->win, 50, 460, 0x00FF0000, "UNLOCKED MOVE RIGHT");
	}
}
