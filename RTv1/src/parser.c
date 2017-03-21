#include "../rtv1.h"

static void		ft_parse_plane(t_env *env, t_buff *line)
{
	t_plane		*plane;
	double		tmp;

	plane = (t_plane*)malloc(sizeof(t_plane));
	ft_parse_not(line, "-0123456789");
	plane->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->pos.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->normal.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->normal.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->normal.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->color.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->color.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->color.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->reflectivity = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->transparency = ft_parse_double(line);
	ft_array_add(env->plane, plane);
}

static void		ft_parse_sphere(t_env *env, t_buff *line)
{
	t_sphere	*sphere;
	double		tmp;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	ft_parse_not(line, "-0123456789");
	sphere->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->pos.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->radius = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->color.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->color.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->color.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->reflectivity = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->transparency = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->emission.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->emission.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->emission.z = ft_parse_double(line);	
	ft_array_add(env->sphere, sphere);
}

void			ft_load_file(int fd, t_env *env)
{
	t_buff		line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line.data[0] == 'S')
			ft_parse_sphere(env, &line);
		// if (line.data[0] == 'P')
		// 	ft_parse_plane(env, &line);
	}
}
