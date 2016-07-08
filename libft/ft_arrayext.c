#include "libft.h"

int			ft_arrayext(t_array *array, int need)
{
	void			**tmp;
	int				len;

	need += array->length + 1;
	if (need < array->alloc_length)
		return (1);
	len = array->alloc_length - 1;
	while (need >= len)
		len += 24;
	if ((tmp = (void**)malloc(sizeof(void*) * len)) == NULL)
		return (0);
	array->alloc_length = len;
	if (array->data != NULL)
	{
		ft_memmove(tmp, array->data, sizeof(void*) * array->length);
		ft_bzero(tmp + array->length, len - array->length);
		free(array->data);
	}
	else
		ft_bzero(tmp, len);
	array->data = tmp;
	return (1);
}