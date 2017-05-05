#include "../rtv1.h"

static char	*take_balise_value(t_env *env, t_pars *pars, char *line, int i)
{
	int		j;
	char	*value;

	j = 0;
	value = (char*)malloc(sizeof(char) * (ft_strlen(line) + 1));
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
			pars_error(env, pars, "Syntax Error : Close type value with ';'.", 1);
		else
			return (value);
	}
	else
		pars_error(env, pars, "Syntax Error.\n", 1);
	return (NULL);
}

static char	*value_of_balise(t_env *env, t_pars *pars, char *line, char *type)
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
			value = take_balise_value(env, pars, line, i);
			return (value);
		}
		i++;
	}
	pars_error(env, pars, "Error : Bad Type Value.", 1);
	return (NULL);
}

static char	*analyse_balise_lign(t_env *env, t_pars *pars, char *line, char *type)
{
	char	*value;

	if (ft_strstr(line, type) != NULL)
	{
		if ((value = value_of_balise(env, pars, line, type)) == NULL)
			return (NULL);
		else
			return (value);
	}
	return (NULL);
}

static void	pars_balise_obj(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	value = analyse_balise_lign(env, pars, line.data, "name=");
	if (value != NULL)
		check_object_name(env, value, pars);
	value = analyse_balise_lign(env, pars, line.data, "color=");
	if (value != NULL)
		check_color_obj(env, pars, &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line.data, "gloss=");
	if (value != NULL)
		add_double_param(line, "gloss", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line.data, "transp=");
	if (value != NULL)
		add_double_param(line, "transp", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line.data, "reflex=");
	if (value != NULL)
		add_double_param(line, "reflex", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line.data, "refraction=");
	if (value != NULL)
		add_double_param(line, "refraction", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line.data, "decoupe=");
	if (value != NULL)
		add_OnOff_value(&env->scene->object, value, pars);
	if (value != NULL)
		free(value);
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
		value = analyse_balise_lign(env, pars, line.data, "name=");
		if (value != NULL)
			check_object_name(env, value, pars);
		value = analyse_balise_lign(env, pars, line.data, "color=");
		if (value != NULL)
			check_color_light(env, pars, &env->scene->light, value);
		pars->balise = 2;
	}
	else if (ft_strstr(line.data, "<HEAD>") != NULL)
		pars->balise = 3;
	else if (ft_strstr(line.data, "<Camera>") != NULL)
		pars->balise = 4;
	else if (ft_strstr(line.data, "<NegObj>") != NULL)
	{
		init_neg_obj(env, pars, &env->scene->negobj);
		pars->nbr_lign = 3;
		pars->balise = 5;
	}
	else
		empty_lign(line);
	if (pars->balise == 2 || pars->balise == 4)
		pars->nbr_lign = 2;
}
