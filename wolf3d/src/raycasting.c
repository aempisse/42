#include "../wolf3d.h"

void			ft_put_image(t_image *img, int pos, t_color color)
{
	int			to;

	to = pos + img->opp;
	while (pos < to)
	{
		img->data[pos] = color.b.b;
		color.u >>= 8;
		pos++;
	}
}

void			raycasting_init(t_env *env, int x)
{
	env->camera = 2 * x / (double)WIDTH - 1;
	env->ray_pos = env->pos;
	env->ray_dir.x = env->dir.x + env->plane.x * env->camera;
	env->ray_dir.y = env->dir.y + env->plane.y * env->camera;
	env->map_pos = (t_pt){(int)env->ray_pos.x, (int)env->ray_pos.y};
	env->delta_dist.x = sqrt(1 + (env->ray_dir.y * env->ray_dir.y) /
		(env->ray_dir.x * env->ray_dir.x));
	env->delta_dist.y = sqrt(1 + (env->ray_dir.x * env->ray_dir.x) /
		(env->ray_dir.y * env->ray_dir.y));
	env->step.x = (env->ray_dir.x < 0) ? -1 : 1;
	env->step.y = (env->ray_dir.y < 0) ? -1 : 1;
	env->side_dist.x = (env->ray_dir.x < 0) ?
		((env->ray_pos.x - env->map_pos.x) * env->delta_dist.x) :
		(env->map_pos.x + 1.0 - env->ray_pos.x) * env->delta_dist.x;
	env->side_dist.y = (env->ray_dir.y < 0) ?
		((env->ray_pos.y - env->map_pos.y) * env->delta_dist.y) :
		(env->map_pos.y + 1.0 - env->ray_pos.y) * env->delta_dist.y;
}

void			raycasting_dda(t_env *env)
{
	while (env->map[env->map_pos.x][env->map_pos.y] == 0)
	// while (TG(int, AG(t_tab*, env->map, env->map_pos.y), env->map_pos.x) == 0)
	{
		if (env->side_dist.x < env->side_dist.y)
		{
			env->side_dist.x += env->delta_dist.x;
			env->map_pos.x += env->step.x;
			if (env->pos.x < env->map_pos.x)
				env->side = WEST;
			else
				env->side = EAST;
		}
		else
		{
			env->side_dist.y += env->delta_dist.y;
			env->map_pos.y += env->step.y;
			if (env->pos.y < env->map_pos.y)
				env->side = NORTH;
			else
				env->side = SOUTH;
		}
	}
}

void			raycasting_draw(t_env *env, int x, int line_height)
{
	int			draw_start;
	int			draw_end;
	int			y;
	t_color		color;

	if ((draw_start = (-line_height / 2) + (HEIGHT / 2)) < 0)
    		draw_start = 0;
    if ((draw_end = (line_height / 2) + (HEIGHT / 2)) >= HEIGHT)
    		draw_end = HEIGHT - 1;
    y = -1;
    while (++y < HEIGHT)
    {
    	color = env->color(env, y, draw_start, draw_end);
    	ft_put_image(env->img, (WIDTH * y + x) * env->img->opp, color);
    }
}

void			raycasting(t_env *env)
{
	int			x;
	double		wall_dist;
	int			line_height;

	x = -1;
	while (++x < WIDTH)
	{
		raycasting_init(env, x);
		raycasting_dda(env);		
		wall_dist = (env->side == 0 || env->side == 1) ?
			(env->map_pos.x - env->ray_pos.x + (1 - env->step.x) / 2) / env->ray_dir.x :
			(env->map_pos.y - env->ray_pos.y + (1 - env->step.y) / 2) / env->ray_dir.y;
		if (wall_dist == 0)
			line_height = HEIGHT;
		else
			line_height = (int)(((double)HEIGHT / wall_dist) * 1.2);
		raycasting_draw(env, x, line_height);
	}
	env->render = 1;
}
