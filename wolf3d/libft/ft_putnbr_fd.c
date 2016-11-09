/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 22:11:47 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/09 19:35:29 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		div;

	div = 1;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	else
		n = -n;
	while (n / div <= -10)
		div *= 10;
	while (div)
	{
		ft_putchar_fd('0' - n / div % 10, fd);
		div /= 10;
	}
}
