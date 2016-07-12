/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 20:35:19 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/04 21:33:40 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n != 0)
	{
		*((char*)dst) = *((char*)src);
		dst++;
		src++;
		if (*((char*)dst - 1) == (char)c)
			return (dst);
		n--;
	}
	return (NULL);
}
