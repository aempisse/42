#include "libft.h"

void			ft_array_kill(void *array, void (*f)(void *data))
{
	if (f != NULL)
		ft_array_clr((t_array*)array, f);
	if (array != NULL)
	{
		if (((t_array*)array)->data != NULL)
			free(((t_array*)array)->data);
		free(array);
	}
}