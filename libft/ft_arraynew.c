#include "libft.h"

t_array			*ft_arraynew(void)
{
	t_array			*array;

	array = (t_array*)malloc(sizeof(t_array));
	if (array == NULL)
		return (NULL);
	ft_arrayini(array);
	return (array);
}