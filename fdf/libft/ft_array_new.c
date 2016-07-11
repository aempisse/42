#include "libft.h"

t_array			*ft_array_new(void)
{
	t_array		*array;

	array = (t_array*)malloc(sizeof(t_array));
	if (array == NULL)
		return (NULL);
	ft_array_ini(array);
	return (array);
}