#include "libft.h"

t_tab			*ft_tabnew(int size)
{
	t_tab			*tab;

	tab = (t_tab*)malloc(sizeof(t_tab));
	if (tab == NULL)
		return (NULL);
	ft_tabini(tab, size);
	return (tab);
}