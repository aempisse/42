#include "libft.h"

double			ft_parse_double(t_buff *buff)
{
	double			nb;
	double			part;
	int				negatif;
	int				part_len;

	negatif = (buff->data[buff->i] == '-') ? 1 : 0;
	if (buff->data[buff->i] == '-' || buff->data[buff->i] == '+')
		buff->i++;
	nb = 0.0;
	while (buff->i < buff->length && ft_isdigit(buff->data[buff->i]))
		nb = nb * 10 + (buff->data[buff->i++] - '0');
	if (buff->data[buff->i] == '.' || buff->data[buff->i] == ',')
	{
		part = 0.0;
		part_len = 0;
		while (ft_isdigit(buff->data[++buff->i]))
			part_len++;
		while (ft_isdigit(buff->data[--buff->i]))
			part = (part + (buff->data[buff->i] - '0')) / 10.0;
		nb += part;
		buff->i += part_len + 1;
	}
	return (negatif ? -nb : nb);
}