#include "libft.h"

void			ft_parsespace(t_buff *buff)
{
	while (buff->i < buff->length && ft_isspace(buff->data[buff->i]))
		buff->i++;
}