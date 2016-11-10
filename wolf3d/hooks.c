#include "wolf3d.h"

int				loop_hook(t_env *env)
{
	if (env->render == 1)
	{
		expose_hook(env);
		printf("\npos.x = %f\npos.y = %f", env->pos.x, env->pos.y);
		printf("\ndir.x = %f\ndir.y = %f", env->dir.x, env->dir.y);
		printf("\nplane.x = %f\nplane.y = %f", env->plane.x, env->plane.y);
		printf("\n");
		env->render = 0;
	}
	return (0);
}

int				expose_hook(t_env *env)
{
	raycasting(env);	
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

int				key_hook(int keycode, t_env *env)
{
	double			move_speed;
	double			rot_speed;
	double			old_dir_x;
	double			old_plane_x;

	move_speed = 0.3;
	rot_speed = 0.1;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65361) // left
	{
		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(rot_speed) - env->dir.y * sin(rot_speed);
		env->dir.y = old_dir_x * sin(rot_speed) + env->dir.y * cos(rot_speed);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(rot_speed) - env->plane.y * sin(rot_speed);
		env->plane.y = old_plane_x * sin(rot_speed) + env->plane.y * cos(rot_speed);
	}
	else if (keycode == 65363) // right
	{
		old_dir_x = env->dir.x;
		env->dir.x = env->dir.x * cos(-rot_speed) - env->dir.y * sin(-rot_speed);
		env->dir.y = old_dir_x * sin(-rot_speed) + env->dir.y * cos(-rot_speed);
		old_plane_x = env->plane.x;
		env->plane.x = env->plane.x * cos(-rot_speed) - env->plane.y * sin(-rot_speed);
		env->plane.y = old_plane_x * sin(-rot_speed) + env->plane.y * cos(-rot_speed);
	}
	else if (keycode == 65362) // up
	{
		if (TG(int, AG(t_tab*, env->map, (int)env->pos.y), (int)(env->pos.x + env->dir.x * move_speed)) == 0)
			env->pos.x += env->dir.x * move_speed;
		if (TG(int, AG(t_tab*, env->map, (int)(env->pos.y + env->dir.y * move_speed)), (int)(env->pos.x)) == 0)
			env->pos.y += env->dir.y * move_speed;
	}
	else if (keycode == 65364) // down
	{
		if (TG(int, AG(t_tab*, env->map, (int)env->pos.y), (int)(env->pos.x - env->dir.x * move_speed)) == 0)
			env->pos.x -= env->dir.x * move_speed;
		if (TG(int, AG(t_tab*, env->map, (int)(env->pos.y - env->dir.y * move_speed)), (int)(env->pos.x)) == 0)
			env->pos.y -= env->dir.y * move_speed;
	}
	else
		return (0);
	env->render = 1;
	return (0);
}
