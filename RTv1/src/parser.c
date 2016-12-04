#include "../rtv1.h"

static void		ft_parse_sphere(t_env *env, t_sphere *sphere, t_buff *line)
{
	double		tmp;

	ft_parse_not(line, "-0123456789");
	sphere->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->pos.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->radius = ft_parse_double(line);
}

void			ft_load_file(int fd, t_env *env)
{
	t_buff		line;
	t_sphere	*tmp;

	while (get_next_line(fd, &line) > 0)
	{
		if (line.data[0] == 'S')
		{
			tmp = (t_sphere*)malloc(sizeof(t_sphere));
			ft_parse_sphere(env, tmp, &line);
			printf("pos.x = %f\npos.y = %f\npos.z = %f\nradius = %f\n\n"
				, tmp->pos.x, tmp->pos.y, tmp->pos.z, tmp->radius);
			ft_tab_add(env->sphere, tmp);
		}
	}
}
