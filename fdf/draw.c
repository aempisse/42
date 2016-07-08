#include "fdf.h"

void			ft_put_image(t_image *img, int pos, t_color color)
{
	int				to;

	to = pos + img->opp;
	while (pos < to)
	{
		img->data[pos] = color.b.b;
		color.i >>= 8;
		pos++;
	}
}

void			ft_draw_point(t_env *env, t_pos pos)
{
	t_pt			pt;

	pos.x *= env->pt_dist;
	pos.y *= env->pt_dist;
	pt = ft_project_iso(pos);
	pt.x += env->offset.x;
	pt.y += env->offset.y;
	if (pt.x < 0 || pt.x >= env->img->width || pt.y < 0 || pt.y >= env->img->height)
		return ;
	ft_put_image(env->img, (env->img->width * pt.y + pt.x) * env->img->opp, ft_get_color(env->color, 
		ft_posd(env->min_z, env->max_z, pos.z)));
}

void			ft_draw_line(t_env *env, t_pos p1, t_pos p2)
{
	t_pos			delta;
	double			pts;

	delta = POS(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
	pts = MAX(MAX(ABS(delta.x), ABS(delta.y)) * env->pt_dist, ABS(delta.z));
	delta.x /= pts;
	delta.y /= pts;
	delta.z /= pts;
	while (--pts >= -1)
	{
		ft_draw_point(env, p1);
		p1.x += delta.x;
		p1.y += delta.y;
		p1.z += delta.z;
	}
}

void			ft_draw_map(t_env *env)
{
	t_pt			pt;
	t_pos			pos;
	t_tab			*tmp;
	double			pt_h;

	pt = PT(0, -1);
	pt_h = env->pt_dist / 10;
	while (++pt.y < env->map->length)
	{
		tmp = (t_tab*)(((t_array*)(env->map))->data[pt.y]);
		pt.x = -1;
		while (++pt.x < tmp->length)
		{
			pos = POS(pt.x, pt.y, TG(double, tmp, pt.x) * pt_h);
			if (pt.x + 1 < tmp->length)
				ft_draw_line(env, pos, POS(pt.x + 1, pt.y,
					TG(double, tmp, pt.x + 1) * pt_h));
			if (pt.y > 0 && pt.x < AG(t_tab*, env->map, pt.y - 1)->length)
				ft_draw_line(env, pos, POS(pt.x, pt.y - 1,
					TG(double, AG(t_tab*, env->map, pt.y - 1), pt.x) * pt_h));
		}
	}
}
