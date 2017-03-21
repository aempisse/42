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
	plane->ior = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	plane->material = ft_parse_int(line);
	ft_array_add(env->objects->planes, plane);
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
	sphere->ior = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	sphere->material = ft_parse_int(line);
	ft_array_add(env->objects->spheres, sphere);
}

static void		ft_parse_light(t_env *env, t_buff *line)
{
	t_light		*light;
	double		tmp;

	light = (t_light*)malloc(sizeof(t_light));
	ft_parse_not(line, "-0123456789");
	light->pos.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->pos.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->pos.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.z = ft_parse_double(line);
	ft_array_add(env->objects->lights, light);
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
		if (line.data[0] == 'L')
			ft_parse_light(env, &line);
	}
}
