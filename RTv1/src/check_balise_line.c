#include "../rtv1.h"

static char	*take_balise_value(char *line, int i)
{
	int		j;
	char	*value;

	j = 0;
	value = (char*)malloc(sizeof(char) * ft_strlen(line));
	if (line[i - 1] == '=')
	{
		while (line[i] != '\0' && line[i] != ';')
		{
			value[j] = line[i];
			i++;
			j++;
		}
		value[j] = '\0';
		if (line[i] != ';')
			ft_error("Syntax Error : Close type value with ';'.\n");
		else
			return (value);
	}
	else
		ft_error("Syntax Error.\n");
	return (value);
}

static char	*value_of_balise(char *line, char *type)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == type[j] && type[j] != '\0')
			j++;
		if (type[j] == '\0')
		{
			i++;
			value = take_balise_value(line, i);
			return (value);
		}
		i++;
	}
	ft_putendl("Error : Bad Type Value.");
	return (NULL);
}

static char	*analyse_balise_lign(char *line, char *type)
{
	char	*value;

	if (ft_strstr(line, type) != NULL)
	{
		if ((value = value_of_balise(line, type)) == NULL)
			return (NULL);
		else
			return (value);
	}
	return (NULL);
}

static void	pars_balise_obj(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	value = analyse_balise_lign(line.data, "name=");
	check_object_name(env, value, pars);
	value = analyse_balise_lign(line.data, "color=");
	if (value != NULL)
		check_color_obj(&env->scene->object, value);
	value = analyse_balise_lign(line.data, "gloss=");
	if (value != NULL)
		add_double_param(line, "gloss", &env->scene->object);
	value = analyse_balise_lign(line.data, "transp=");
	if (value != NULL)
		add_double_param(line, "transp", &env->scene->object);
	value = analyse_balise_lign(line.data, "reflex=");
	if (value != NULL)
		add_double_param(line, "reflex", &env->scene->object);
	value = analyse_balise_lign(line.data, "refraction=");
	if (value != NULL)
		add_double_param(line, "refraction", &env->scene->object);
	value = analyse_balise_lign(line.data, "decoupe=");
	if (value != NULL && ft_strcmp(value, "On") == 0)
		pars->nbr_lign = 7;
}

void		check_object_balise(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	if (ft_strstr(line.data, "<Object>") != NULL)
	{
		pars->nbr_lign = 3;
		pars_balise_obj(env, line, pars);
		pars->balise = 1;
	}
	else if (ft_strstr(line.data, "<LightObj>") != NULL)
	{
		pars->nbr_lign = 2;
		value = analyse_balise_lign(line.data, "name=");
		check_object_name(env, value, pars);
		value = analyse_balise_lign(line.data, "color=");
		if (value != NULL)
			check_color_light(&env->scene->light, value);
		pars->balise = 2;
	}
	else if (ft_strstr(line.data, "<Camera>") != NULL)
	{
		pars->nbr_lign = 2;
		pars->balise = 3;
	}
	else
		empty_lign(line);
}
