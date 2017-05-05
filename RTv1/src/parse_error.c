#include "../rtv1.h"

int			pars_error(t_env *env, t_pars *pars, char *message, int act)
{
	char		*str;
	char		*ligne;
	char		*tmp;

	str = (char*)malloc(sizeof(char) * ft_strlen(message) + 20);
	tmp = (char*)malloc(sizeof(char) * ft_strlen(message) + 1);
	ligne = ft_itoa(pars->ligne);
	str = ft_strcpy(str, "Ligne ");
	str = ft_strjoin(str, ligne);
	str = ft_strjoin(str, " : ");
	str = ft_strjoin(str, message);
	ft_putendl(str);
	if (act == 0)
	{
		pars->balise = -pars->balise;
//		delete_current_obj(env, pars);
	}
	return (0);
}