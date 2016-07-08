/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:52:00 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:43:30 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		len_dest;
	size_t		len_src;
	int			i;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size < len_dest)
		return (size + len_src);
	i = -1;
	while (src[++i] != '\0' && (len_dest + i + 1) < size)
		dst[len_dest + i] = src[i];
	dst[len_dest + i] = '\0';
	return (len_dest + len_src);
}
