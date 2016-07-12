/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 20:03:38 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 20:03:46 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	size_t			len;

	if (!s)
		return (0);
	i = 0;
	while (ft_isspace(s[i]) || s[i] == '\n')
		i++;
	len = ft_strlen(s) - 1;
	while (len && (ft_isspace(s[len]) || s[len] == '\n'))
		len--;
	if (len < i)
		return (ft_strdup (""));
	return (ft_strsub(s, i, len - (size_t)i + 1));
}
