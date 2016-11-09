/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 22:04:53 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:33:47 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	int		div;

	div = 1;
	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	if (n < 0)
		ft_putchar('-');
	else
		n = -n;
	while (n / div <= -10)
		div *= 10;
	while (div)
	{
		ft_putchar('0' - n / div % 10);
		div /= 10;
	}
}
