#include "../rtv1.h"

static void		check_object_name(t_env *env, t_buff line, t_buff *object)
{
	if (ft_isalpha(line.data[0]) == 1)
	{
		if (ft_strcmp(line.data, "Sphere") == 0)
			object->data = "Sphere";
		else if (ft_strcmp(line.data, "Plane") == 0)
			object->data = "Plane";
		else if (ft_strcmp(line.data, "Cylinder") == 0)
			object->data = "Cylinder";
		else if (ft_strcmp(line.data, "Cone") == 0)
			object->data = "Cone";
		else if (ft_strcmp(line.data, "Light") == 0)
			object->data = "Light";
		else
			ft_error("Error : Wrong object name.\n");
		init_object(env, object->data);
		object->i = 1;
	}
	else
	  	ft_error("Error : No Object Name/Bad space.\n");
}

static void		incr_nbr_line(t_buff *object)
{
	if (ft_strcmp(object->data, "Sphere") == 0)
		object->length = 5;
	if (ft_strcmp(object->data, "Plane") == 0)
		object->length = 5;
	if (ft_strcmp(object->data, "Cylinder") == 0)
		object->length = 6;
	if (ft_strcmp(object->data, "Cone") == 0)
		object->length = 6;
	if (ft_strcmp(object->data, "Light") == 0)
		object->length = 2;
}

static void		choose_pars_obj_test(t_env *env, t_buff line, t_buff *object, int i)
{
	if (ft_strcmp(object->data, "Sphere") == 0)
		check_sphere_obj(env, line, i);
	else if (ft_strcmp(object->data, "Plane") == 0)
		check_plane_obj(env, line, i);
	else if (ft_strcmp(object->data, "Cylinder") == 0)
		check_cylinder_obj(env, line, i);
	else if (ft_strcmp(object->data, "Cone") == 0)
	 	check_cone_obj(env, line, i);
	else if (ft_strcmp(object->data, "Light") == 0)
		check_light_obj(env, line, i);
}

static int		check_object_line_value(t_env *env, int fd, t_buff line,
										t_buff *object, int j)
{
	incr_nbr_line(object);
	choose_pars_obj_test(env, line, object, j);
	j++;
	if (j == object->length)
	{
		object->i = 0;
		j = 0;
	}
	return (j);
}

void		check_files(int fd, t_env *env)
{
	t_buff		line;
	t_buff		*object;
	int			j;

	j = 0;
	object = (t_buff*)malloc(sizeof(t_buff*));
	object->i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line.data);
		if (object->i == 0)
			check_object_name(env, line, object);
		else if (object->i == 1)
			j = check_object_line_value(env, fd, line, object, j);
	}
	free(object);
}