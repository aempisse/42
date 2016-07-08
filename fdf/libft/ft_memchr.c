/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 20:42:54 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/08 20:42:55 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ret;
	size_t			i;

	ret = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (ret[i] == (unsigned char)c)
			return ((void*)&ret[i]);
		i++;
	}
	return (NULL);
}
