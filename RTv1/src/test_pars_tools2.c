#include "../rtv1.h"

void			empty_lign(t_buff line)
{
	ft_parse_space(&line);
	if (line.data[line.i] != '\0')
		ft_error("Error : not an empty line between <Object>.\n");
}

void			test_decoup_balise(char *line, int i)
{
	if (i == 3)
	{
		if (ft_strstr(line, "<decoupe>") != NULL)
			return ;
		else
			ft_error("Balise Error : <decoupe>");
	}
	else if (i == 6)
	{
		if (ft_strstr(line, "<decoupe/>") != NULL)
			return ;
		else
			ft_error("Balise Error : <decoupe/>");
	}
}
