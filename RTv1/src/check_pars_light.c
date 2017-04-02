#include "../rtv1.h"

void		check_light_obj(t_env *env, t_buff line, int i)
{
	t_double3	*values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			pick_values(line, values, 3);
			add_light_value(env, values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	else if (i == 1)
	{
		if (ft_strstr(line.data, "Color") != NULL)
		{
			check_pars_nbr_value(line, 3);
			pick_values(line, values, 3);
			add_light_value(env, values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}