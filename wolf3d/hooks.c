#include "wolf3d.h"

int				loop_hook(t_env *env)
{
	if (env->render == 1)
	{
		expose_hook(env);
		printf("\npos.x = %f\npos.y = %f", env->pos.x, env->pos.y);
		printf("\nray_pos.x = %f\nray_pos.y = %f", env->ray_pos.x, env->ray_pos.y);
		printf("\ndir.x = %f\ndir.y = %f", env->dir.x, env->dir.y);
		printf("\nmap_pos.x = %d\nmap_pos.y = %d", env->map_pos.x, env->map_pos.y);
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

	move_speed = 0.3;
	rot_speed = 0.1;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65361) // left
	{
		env->old_dir.x = env->dir.x;
		env->dir.x = env->dir.x * cos(rot_speed) - env->dir.y * sin(rot_speed);
		env->dir.y = env->old_dir.x * sin(rot_speed) + env->dir.y * cos(rot_speed);
		env->old_plane.x = env->plane.x;
		env->plane.x = env->plane.x * cos(rot_speed) - env->dir.y * sin(rot_speed);
		env->plane.y = env->old_plane.x * sin(rot_speed) + env->dir.y * cos(rot_speed);
	}
	else if (keycode == 65363) // right
	{
		env->old_dir.x = env->dir.x;
		env->dir.x = env->dir.x * cos(-rot_speed) - env->dir.y * sin(-rot_speed);
		env->dir.y = env->old_dir.x * sin(-rot_speed) + env->dir.y * cos(-rot_speed);
		env->old_plane.x = env->plane.x;
		env->plane.x = env->plane.x * cos(-rot_speed) - env->dir.y * sin(-rot_speed);
		env->plane.y = env->old_plane.x * sin(-rot_speed) + env->dir.y * cos(-rot_speed);
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
