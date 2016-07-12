#include "libft.h"

void			ft_parse_not(t_buff *buff, const char *parse)
{
	while (buff->i < buff->length)
	{
		if (ft_strchr(parse, buff->data[buff->i]) != NULL)
			break ;
		buff->i++;
	}
}