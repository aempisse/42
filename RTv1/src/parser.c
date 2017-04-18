#include "../rtv1.h"

static void		ft_parse_camera(t_scene *scene, t_buff *line)
{
	ft_parse_not(line, "-0123456789");
	scene->camera.position.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	scene->camera.position.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	scene->camera.position.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	scene->camera.direction.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	scene->camera.direction.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	scene->camera.direction.z = ft_parse_double(line);
}

static void		ft_parse_object(t_scene *scene, t_buff *line, int object_type)
{
	t_object	*object;

	object = object_new();
	object->type = object_type;
	ft_parse_not(line, "-0123456789");
	object->position.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->position.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->position.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->rotation.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->rotation.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->rotation.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->radius = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->color.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->color.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->color.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->reflexion = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	object->transparency = ft_parse_int(line);
	ft_parse_not(line, "-0123456789");
	object->gloss = ft_parse_int(line);
	ft_parse_not(line, "-0123456789");
	object->refraction = ft_parse_int(line);
	object_add(&(scene->objects), object);
}

static void		ft_parse_light(t_scene *scene, t_buff *line)
{
	t_light		*light;

	light = light_new();
	ft_parse_not(line, "-0123456789");
	light->position.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->position.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->position.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->direction.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->direction.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->direction.z = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.x = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.y = ft_parse_double(line);
	ft_parse_not(line, "-0123456789");
	light->color.z = ft_parse_double(line);
	light_add(&(scene->lights), light);
}

void			ft_load_file(int fd, t_scene *scene)
{
	t_buff		line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line.data[0] == 'X')
			ft_parse_camera(scene, &line);
		if (line.data[0] == 'S')
			ft_parse_object(scene, &line, SPHERE);
		if (line.data[0] == 'P')
			ft_parse_object(scene, &line, PLANE);
		if (line.data[0] == 'C')
			ft_parse_object(scene, &line, CYLINDER);
		if (line.data[0] == 'O')
			ft_parse_object(scene, &line, CONE);
		if (line.data[0] == 'L')
			ft_parse_light(scene, &line);
	}
}
