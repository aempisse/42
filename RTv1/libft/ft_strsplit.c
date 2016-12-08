/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 20:00:44 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 20:01:08 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(const char *s, char c)
{
	char	**ret;
	size_t	j;
	size_t	len;

	if (!c)
		return (0);
	if ((ret = ft_memalloc(ft_strlen(s) + 1)) == NULL)
		return (NULL);
	j = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			len = 0;
			while (s[len] && (s[len] != c))
				len++;
			ret[j++] = ft_strsub(s, 0, len);
			s += len;
		}
	}
	ret[j] = 0;
	return (ret);
}
