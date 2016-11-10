#include "wolf3d.h"

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

void			raycasting(t_env *env)
{
	int			x;
	int			y;
	int			side;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_color		color;

	x = -1;
	while (++x < WIDTH)
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

		// if (env->ray_dir.x < 0)
		// {
		// 	env->step.x = -1;
		// 	env->side_dist.x = (env->ray_pos.x - env->map_pos.x) * env->delta_dist;
		// }
		// else
		// {
		// 	env->step.x = 1;
		// 	env->side_dist.x = (env->map_pos.x + 1.0 - env->ray_pos.x) * env->delta_dist.x;
		// }
		// if (env->ray_dir.y < 0)
		// {
		// 	env->step.y = -1;
		// 	env->side_dist.y = (env->ray_pos.y - env->map_pos.y) * env->delta_dist.y;
		// }
		// else
		// {
		// 	env->step.y = 1;
		// 	env->side_dist.y = (env->map_pos.y + 1.0 - env->ray_pos.y) * env->delta_dist.y;
		// }

		while (TG(int, AG(t_tab*, env->map, env->map_pos.y), env->map_pos.x) == 0)
		{
			if (env->side_dist.x < env->side_dist.y)
			{
				env->side_dist.x += env->delta_dist.x;
				env->map_pos.x += env->step.x;
				side = 0;
			}
			else
			{
				env->side_dist.y += env->delta_dist.y;
				env->map_pos.y += env->step.y;
				side = 1;
			}
		}

		wall_dist = (side == 0) ?
			(env->map_pos.x - env->ray_pos.x + (1 - env->step.x) / 2) / env->ray_dir.x :
			(env->map_pos.y - env->ray_pos.y + (1 - env->step.y) / 2) / env->ray_dir.y;
		if (wall_dist == 0)
			line_height = HEIGHT;
		else
			line_height = (int)(((double)HEIGHT / wall_dist) * 1.0);

    	if ((draw_start = (-line_height / 2) + (HEIGHT / 2)) < 0)
    		draw_start = 0;
    	if ((draw_end = (line_height / 2) + (HEIGHT / 2)) >= HEIGHT)
    		draw_end = HEIGHT - 1;
    	y = -1;
    	while (++y < HEIGHT)
    	{
    		if (y < draw_start)
    			color.u = 0x00778899;
    		else if (y < draw_end)
    		{
    			color.u = 0x000000FF;
    			if (side == 1)
    				color.u -= 0x44; 
    		}
    		else
    			color.u = 0x00DEB887;
    		ft_put_image(env->img, (WIDTH * y + x) * env->img->opp, color);
    	}
	}
	env->render = 1;
}
