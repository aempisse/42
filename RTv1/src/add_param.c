#include "../rtv1.h"

void			add_OnOff_value(t_object **object, char *value, t_pars *pars)
{
	t_object	*tmp;

	tmp = *object;
	if (strcmp(value, "On") == 0)
	{
		pars->nbr_lign = 8;
		tmp->dcp = 1;
	}
	else if (strcmp(value, "Off") == 0)
		tmp->dcp = 0;
	else
		ft_error("Error : Wrong Off/On Value.\n");
}

static int	search_param(char *line, char *type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		while (line[i] != '\0' && line[i] != '\n' && line[i] == type[j])
		{
			i++;
			j++;
			if (type[j] == '\0')
				return (i + 1);
		}
		j = 0;
		i++;
	}
	return (-1);
}

void		add_double_param(t_buff line, char *type, t_object **object, char *value)
{
	t_object	*tmp;

	tmp = *object;
	line.i = search_param(line.data, type);
	if (ft_strcmp(type, "gloss") == 0)
		tmp->gloss = ft_parse_double(&line);
	else if (ft_strcmp(type, "transp") == 0)
		tmp->transparency = ft_parse_double(&line);
	else if (ft_strcmp(type, "refraction") == 0)
		tmp->refraction = ft_parse_double(&line);
	else if (ft_strcmp(type, "reflex") == 0)
		tmp->reflex = ft_parse_double(&line);
	if (value != NULL)
		free(value);
}
