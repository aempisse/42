#include "../rtv1.h"

static int		end_balise(t_buff line, t_pars *pars)
{
	char	*str;

	if (pars->balise == 1 && ft_strcmp(line.data, "<Object/>") == 0)
		return (1);
	else if (pars->balise == 2 && ft_strcmp(line.data, "<LightObj/>") == 0)
		return (1);
	else if (pars->balise == 3 && ft_strcmp(line.data, "<Camera/>") == 0)
		return (1);
	return (0);
}

static int		check_object_line_value(t_env *env, t_buff line,
										t_pars *pars, int j)
{
	if (end_balise(line, pars) == 1)
	{
		if (j == pars->nbr_lign)
		{
			pars->balise = 0;
			j = 0;
		}
		else
			ft_error("Error : Wrong Number of Values Lines.\n");
	}
	if (pars->balise == 1)
		pars_object_line(env, line, j++);
	else if (pars->balise == 2)
		pars_light_line(env, line, j++);
	else if (pars->balise == 3)
		pars_camera_line(env, line, j++);
	if (j > pars->nbr_lign)
		ft_error("Error : Too Much of Values Lines, Close the Object.\n");
	return (j);
}

static t_pars	*init_parser(void)
{
	t_pars	*pars;

	if ((pars = (t_pars*)malloc(sizeof(t_pars*))) == NULL)
		ft_error("Error : Malloc() failed.\n");
	pars->balise = 0;
	pars->nbr_lign = 0;
	return (pars);
}

void			check_files(int fd, t_env *env)
{
	t_buff		line;
	t_pars		*pars;
	int			j;

	j = 0;
	pars = init_parser();
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line.data);
		if (pars->balise == 0)
			check_object_balise(env, line, pars);
		else if (pars->balise >= 1)
			j = check_object_line_value(env, line, pars, j);
	}
	if (j < pars->nbr_lign && j != 0)
		ft_error("Error : Wrong Number of Line.\n");
}
