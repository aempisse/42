#include "../rtv1.h"

static int		pars_OffOn_line(t_buff line)
{
	char	*str;
	int		i;

	str = ft_strnew(4);
	i = 0;
	ft_parse_not(&line, "<");
	while (line.data[line.i] != '\0' && line.data[line.i] != '>')
		line.i++;
	ft_parse_not(&line, "O");
	while (line.data[line.i] != '\0' && line.data[line.i] != ';')
	{
		str[i] = line.data[line.i];
		i++;
		line.i++;
	}
	str[i] = '\0';
	if (ft_strcmp(str, "ON") == 0)
		i = 1;
	else if (ft_strcmp(str, "OFF") == 0)
		i = 0;
	else
		ft_error("Error : Not a ON/OFF value.\n");
	free(str);
	return (i);
}

static char		*check_line_type(t_buff line)
{
	char	*type;
	int		i;

	type = (char*)malloc(sizeof(char) * (ft_strlen(line.data) + 1));
	i = 0;
	ft_parse_not(&line, "<");
	line.i++;
	while (line.data[line.i] != '\0' && line.data[line.i] != '>')
	{
		type[i] = line.data[line.i];
		i++;
		line.i++;
	}
	type[i] = '\0';
	return (type);
}

void			pars_head_value(t_env *env, t_buff line)
{
	char		*type;
	t_double3	value;

	type = check_line_type(line);
	if (ft_strcmp(type, "Ambiant") == 0)
	{
		check_pars_nbr_value(line, 1);
		value = pick_values(line, 1);
		env->scene->ambiant = value.x;
	}
	else if (ft_strcmp(type, "Aliaising") == 0)
		env->scene->aliaising = pars_OffOn_line(line);
	else if (ft_strcmp(type, "Direct Light") == 0)
		env->scene->direct_light = pars_OffOn_line(line);
	else
		ft_error("Error : Unknow Head Value.\n");
	free(type);
}