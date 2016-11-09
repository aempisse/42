/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 19:56:12 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:56:23 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2 || (!s1 && !s2))
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if ((ret = ft_memalloc(len_s1 + len_s2 + 1)) == NULL)
		return (NULL);
	ft_memcpy(ret, s1, len_s1);
	ft_memcpy(ret + len_s1, s2, len_s2);
	ret[len_s1 + len_s2] = '\0';
	return (ret);
}
