#include "fdf.h"
#include <stdlib.h>

static int			ft_load_line(t_env *env, t_tab *pts, t_buff *line)
{
	double			tmp;
	int			valid;

	valid = 1;
	ft_parsespace(line);
	while (line->data[line->i] != '\0')
	{
		tmp = ft_parsedouble(line);
		env->max_z = MAX(env->max_z, tmp);
		env->min_z = MIN(env->min_z, tmp);
		ft_tabadd(pts, &tmp);
		if (line->data[line->i] != ' ' && line->data[line->i] != '\0')
			valid = 0;
		ft_parsenot(line, " \t\n");
		ft_parsespace(line);
	}
	return (valid);
}

int			ft_load_map(int fd, t_env *env)
{
	t_buff			line;
	t_tab			*tmp;
	int				valid;
//	t_pt			pt;


	valid = 1;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_tabnew(sizeof(double));
		if (!ft_load_line(env, tmp, &line))
			valid = 0;
		ft_arrayadd(env->map, tmp);
	}
	/*
	pt = PT(0, -1);
	while (++pt.y < env->map->length)
	{
		pt.x = -1;
		tmp = (t_tab*)(((t_array*)env->map)->data[pt.y]);
		while (++pt.x < tmp->length)
		{
			printf("%g ", *(double*)(((t_tab*)tmp)->data + ((t_tab*)tmp)->size * pt.x));
		}
		printf("\n");
	}
	*/
	return (valid);
}

static void		ft_get_maxmin(t_env *env, t_pt *max, t_pt *min)
{
	t_pt			i;
	t_tab			*line;
	t_pt			tmp;

	*max = PT(0, 0);
	*min = PT(WIDTH, HEIGHT);
	i = PT(-1, -1);
	while (++i.y < env->map->length)
	{
		line = (t_tab*)(((t_array*)(env->map))->data[i.y]);
		i.x = line->length;
		while (i.x-- > 0)
		{
			tmp = ft_project_iso(POS(i.x * env->pt_dist, i.y * env->pt_dist,
				TG(double, line, i.x) * env->pt_dist / 10));
			max->x = MAX(max->x, tmp.x);
			max->y = MAX(max->y, tmp.y);
			min->x = MIN(min->x, tmp.x);
			min->y = MIN(min->y, tmp.y);
		}
	}
}

void			ft_mapoffset(t_env *env)
{
	t_pt			max;
	t_pt			min;
	t_pt			first;

	env->pt_dist = 1;
	ft_get_maxmin(env, &max, &min);
	env->pt_dist = DEF_PTDIST;
	if (((max.x - min.x) * env->pt_dist) > WIDTH)
		env->pt_dist *= WIDTH / (env->pt_dist * (max.x - min.x + 2));
	if (((max.y - min.y) * env->pt_dist) > HEIGHT)
		env->pt_dist *= HEIGHT / (env->pt_dist * (max.y - min.y + 1));
	ft_get_maxmin(env, &max, &min);
	ft_putstr("ptdist   : ");
	ft_putnbr(env->pt_dist);
	ft_putchar('\n');
	ft_putstr("max_x    : ");
	ft_putnbr(max.x);
	ft_putchar('\n');
	ft_putstr("min_x    : ");
	ft_putnbr(min.x);
	ft_putchar('\n');
	ft_putstr("max_y    : ");
	ft_putnbr(max.y);
	ft_putchar('\n');
	ft_putstr("min_y    : ");
	ft_putnbr(min.y);
	ft_putchar('\n');
	first = ft_project_iso(POS(0, 0, 0));
	env->offset.x = (WIDTH - ((max.x - min.x + first.x))) / 2;
	env->offset.y = (HEIGHT - ((max.y - min.y + first.y))) / 2;
	env->offset.x += (first.x - min.x);
	env->offset.y += (first.y - min.y);
	ft_putstr("offset_x : ");
	ft_putnbr(env->offset.x);
	ft_putchar('\n');
	ft_putstr("offset_y : ");
	ft_putnbr(env->offset.y);
	ft_putchar('\n');
}

t_pt			ft_project_iso(t_pos pos)
{
	t_pt			pt;

	pt.x = ROUND(0.6 * pos.x - 0.6 * pos.y);
	pt.y = ROUND(-pos.z + 0.3 * pos.x + 0.3 * pos.y);
	return (pt);
}
