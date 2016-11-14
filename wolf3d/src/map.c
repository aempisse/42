#include "../wolf3d.h"

// static int		ft_load_line(t_env *env, t_tab *pts, t_buff *line)
// {
// 	int			tmp;
// 	int			valid;

// 	valid = 1;
// 	ft_parse_space(line);
// 	while (line->data[line->i] != '\0')
// 	{
// 		tmp = ft_parse_int(line);
// 		ft_tab_add(pts, &tmp);
// 		if (line->data[line->i] != ' ' && line->data[line->i] != '\0')
// 			valid = 0;
// 		ft_parse_not(line, " \t\n");
// 		ft_parse_space(line);
// 	}
// 	return (valid);
// }

// int				ft_load_map(int fd, t_env *env)
// {
// 	t_buff		line;
// 	t_tab		*tmp;
// 	int			valid;

// 	valid = 1;
// 	while (get_next_line(fd, &line) > 0)
// 	{
// 		tmp = ft_tab_new(sizeof(int));
// 		if (!ft_load_line(env, tmp, &line))
// 			valid = 0;
// 		ft_array_add(env->map, tmp);
// 	}
// 	return (valid);
// }

static int		ft_load_line(t_env *env, int *array, t_buff *line)
{
	int			tmp;
	int			valid;
	int			i;

	valid = 1;
	i = -1;
	ft_parse_space(line);
	while (line->data[line->i] != '\0' && ++i < MAP_WIDTH)
	{
		tmp = ft_parse_int(line);
		array[i] = tmp;
		if (line->data[line->i] != ' ' && line->data[line->i] != '\0')
			valid = 0;
		ft_parse_not(line, " \t\n");
		ft_parse_space(line);
	}
	return (valid);
}

int				ft_load_map(int fd, t_env *env)
{
	t_buff		line;
	int			*tmp;
	int			valid;
	int			i;

	valid = 1;
	i = -1;
	while (get_next_line(fd, &line) > 0 && ++i < MAP_HEIGHT)
	{
		tmp = (int*)malloc(sizeof(int) * MAP_WIDTH);
		if (!ft_load_line(env, tmp, &line))
			valid = 0;
		env->map[i] = tmp;
	}
	return (valid);
}
