#include "libft.h"

void			ft_tabkil(void *tab)
{
	free(((t_tab*)tab)->data);
	free(tab);
}