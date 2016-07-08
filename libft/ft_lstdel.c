/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 22:26:12 by aempisse          #+#    #+#             */
/*   Updated: 2014/12/03 22:26:13 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*lst;
	t_list	*lst_next;

	lst = *alst;
	while (lst != NULL)
	{
		lst_next = lst->next;
		ft_lstdelone(&lst, (*del));
		lst = lst_next;
	}
	*alst = NULL;
}
