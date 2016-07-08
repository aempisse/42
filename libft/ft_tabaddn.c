#include "libft.h"

void			ft_tabaddn(t_tab *tab, const void *add, int n)
{
	const int		bytes = tab->size * n;

	if (!ft_tabext(tab, n))
		return ;
	ft_memmove(tab->data + tab->bytes, add, bytes);
	tab->length += n;
	tab->bytes += bytes;
}