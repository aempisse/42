#include "../wolf3d.h"

void			draw_rect(t_image *img, t_rect rect, t_color color)
{
	int			x;
	int			y;

	y = -1;
	while (rect.b + ++y < rect.b + rect.d)
	{
		x = -1;
		while (rect.a + ++x < rect.a + rect.c)
			ft_put_image(img, (WIDTH * (rect.b + y) + rect.a + x) * img->opp, color);
	}
}

void			minimap(t_env *env)
{
	t_pt			pt;
	t_color			color;
	t_tab			*tmp;

	color.u = 0x00FFFFFF;
	pt.y = -1;
	// while (++pt.y < env->map->length)
	while (++pt.y < MAP_HEIGHT)
	{
		pt.x = -1;
		// tmp = (t_tab*)((t_array*)(env->map)->data[pt.y]);
		// while (++pt.x < tmp->length)
		while (++pt.x < MAP_WIDTH)
		{
			// if (TG(int, tmp, pt.x) == 1)
			if (env->map[pt.x][pt.y] == 1)
				color.u = 0x00000000;
			// else if (TG(int, tmp, pt.x) == 5)
			else if (env->map[pt.x][pt.y] == 5)
				color.u = 0x00FFFFFF;
			else
				color.u = 0x00303030;
			if (pt.x == (int)env->pos.x && pt.y == (int)env->pos.y)
				color.u = 0x00FF0000;
			draw_rect(env->img, (t_rect){pt.x * 8 + 50, pt.y * 8 + 50, 8, 8}, color);
		}
	}
}