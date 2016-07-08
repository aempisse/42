/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:28:37 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:44:59 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;

	if (*to_find == '\0')
		return ((char*)str);
	while (*str != '\0' && n > 0)
	{
		if (*str == *to_find)
		{
			i = 0;
			while (str[i] != '\0' && str[i] == to_find[i])
				i++;
			if (to_find[i] == '\0' && i <= n)
				return ((char*)str);
		}
		str++;
		n--;
	}
	return (NULL);
}
