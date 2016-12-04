/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:26:40 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:36:23 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	len;
	int		i;

	len = ft_strlen(dst);
	i = -1;
	while (src[++i] != '\0')
		dst[len + i] = src[i];
	dst[len + i] = '\0';
	return (dst);
}
