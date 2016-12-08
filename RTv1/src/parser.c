#include "../rtv1.h"

static void		ft_parse_plane(t_env *env, t_buff *line)
{
	t_plane		*tmp;

	tmp = (t_plane*)malloc(sizeof(t_plane));
	ft_parse_not(line, "-0123456789");
	tmp->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	tmp->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	tmp->pos.z = ft_parse_double(line);
	ft_array_add(env->plane, tmp);
}

static void		ft_parse_sphere(t_env *env, t_buff *line)
{
	t_sphere	*tmp;

	tmp = (t_sphere*)malloc(sizeof(t_sphere));	
	ft_parse_not(line, "-0123456789");
	tmp->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	tmp->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	tmp->pos.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	tmp->radius = ft_parse_double(line);
	ft_array_add(env->sphere, tmp);
}

void			ft_load_file(int fd, t_env *env)
{
	t_buff		line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line.data[0] == 'S')
			ft_parse_sphere(env, &line);
		if (line.data[0] == 'P')
			ft_parse_plane(env, &line);
	}
}
