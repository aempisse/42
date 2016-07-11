#include "libft.h"

t_tab			*ft_tab_new(int size)
{
	t_tab			*tab;

	tab = (t_tab*)malloc(sizeof(t_tab));
	if (tab == NULL)
		return (NULL);
	ft_tab_ini(tab, size);
	return (tab);
}