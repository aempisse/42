/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:06:43 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:20:29 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int n)
{
	int		count;

	count = 0;
	if (n <= 0)
	{
		count = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
		return ("-2147483648");
	i = ft_count_digit(n) - 1;
	if ((str = ft_strnew(i + 1)) != NULL)
	{
		if (n == 0)
			*str = '0';
		else if (n < 0)
		{
			*str = '-';
			n = -n;
		}
		while (n > 0)
		{
			str[i] = '0' + (n % 10);
			n /= 10;
			i--;
		}
	}
	return (str);
}

/*char		*free_itoa(int n)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(n);
	str = tmp;
	free(tmp);
	return (str);
}*/
