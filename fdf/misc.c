#include "fdf.h"
#include <stdlib.h>

int				ft_parseint(t_buff *buff)
{
	int				nb;
	int				negatif;

	negatif = (buff->data[buff->i] == '-') ? 1 : 0;
	if (buff->data[buff->i] == '-' || buff->data[buff->i] == '+')
		buff->i++;
	nb = 0;
	while (buff->i < buff->length && ft_isdigit(buff->data[buff->i]))
		nb = nb * 10 + (buff->data[buff->i++] - '0');
	return (negatif ? -nb : nb);
}

double			ft_parsedouble(t_buff *buff)
{
	double			nb;
	double			part;
	int				negatif;

	negatif = (buff->data[buff->i] == '-') ? 1 : 0;
	if (buff->data[buff->i] == '-' || buff->data[buff->i] == '+')
		buff->i++;
	nb = 0.0;
	while (buff->i < buff->length && ft_isdigit(buff->data[buff->i]))
		nb = nb * 10 + (buff->data[buff->i++] - '0');
	if (buff->data[buff->i] == '.' || buff->data[buff->i] == ',')
	{
		part = 0.0;
		while (ft_isdigit(buff->data[++buff->i]))
			;
		while (ft_isdigit(buff->data[--buff->i]))
			part = (part + (buff->data[buff->i] - '0')) / 10.0;
		nb += part;
	}
	return (negatif ? -nb : nb);
}

void			ft_parsespace(t_buff *buff)
{
	while (buff->i < buff->length && ft_isspace(buff->data[buff->i]))
		buff->i++;
}

void			ft_parsenot(t_buff *buff, const char *parse)
{
	while (buff->i < buff->length)
	{
		if (ft_strchr(parse, buff->data[buff->i]) != NULL)
			break ;
		buff->i++;
	}
}