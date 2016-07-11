#include "libft.h"

void			ft_tab_kill(void *tab)
{
	free(((t_tab*)tab)->data);
	free(tab);
}