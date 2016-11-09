/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/13 17:36:52 by aempisse          #+#    #+#             */
/*   Updated: 2015/06/13 17:36:55 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnumber(const char *str)
{
	while (ft_iswhite(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.' || *str == ',')
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhite(*str))
		str++;
	return (*str == '\0') ? 1 : 0;
}
