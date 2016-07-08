#include "libft.h"

void			ft_arrayadd(t_array *array, void *add)
{
	if (!ft_arrayext(array, 1))
		return ;
	array->data[array->length] = add;
	array->length++;
}