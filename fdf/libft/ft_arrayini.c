#include "libft.h"

void			ft_arrayini(t_array *array)
{
	array->data = (void**)malloc(sizeof(void*) * 16);
	if (array->data != NULL)
		ft_bzero(array->data, 16);
	array->length = 0;
	array->alloc_length = (array->data == NULL) ? 0 : 16;
}