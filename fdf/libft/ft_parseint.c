#include "libft.h"

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