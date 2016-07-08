#include "libft.h"

int				ft_tabext(t_tab *tab, int need)
{
	unsigned char	*tmp;
	int				len;

	need = need * tab->size + tab->bytes;
	len = tab->alloc_bytes;
	if (need < len)
		return (1);
	while (need >= len)
		len += 24 * tab->size;
	if ((tmp = (unsigned char*)malloc(sizeof(unsigned char) * len)) == NULL)
		return (0);
	tab->alloc_bytes = len;
	if (tab->data != NULL)
	{
		ft_memcpy(tmp, tab->data, tab->bytes);
		free(tab->data);
	}
	tab->data = tmp;
	return (1);
}