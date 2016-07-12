/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:42:08 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:45:52 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;

	if (*to_find == '\0')
		return ((char*)str);
	while (*str != '\0')
	{
		if (*str == *to_find)
		{
			i = 0;
			while (str[i] != '\0' && str[i] == to_find[i])
				i++;
			if (to_find[i] == '\0')
				return ((char*)str);
		}
		str++;
	}
	return (NULL);
}
