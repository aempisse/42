#include "../rtv1.h"

void		check_camera_obj(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			env->camera.pos = pick_values(line, 3);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	else if (i == 1)
	{
		if (ft_strstr(line.data, "Dir") != NULL)
		{
			check_pars_nbr_value(line, 3);
			env->camera.dir = pick_values(line, 3);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}
