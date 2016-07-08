/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 20:27:20 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/08 20:27:22 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*tmp;

	tmp = ft_memalloc(n);
	tmp = ft_memcpy(tmp, src, n);
	dst = ft_memcpy(dst, tmp, n);
	return (dst);
}
