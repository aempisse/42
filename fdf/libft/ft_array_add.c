#include "libft.h"

void			ft_array_add(t_array *array, void *add)
{
	if (!ft_array_ext(array, 1))
		return ;
	array->data[array->length] = add;
	array->length++;
}