/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 22:26:35 by aempisse          #+#    #+#             */
/*   Updated: 2014/12/03 22:26:37 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*prev;
	t_list	*origin;

	if (!lst || !f)
		return (NULL);
	new = (*f)(lst);
	origin = new;
	prev = new;
	lst = lst->next;
	while (lst != NULL)
	{
		if ((new = (*f)(lst)) == NULL)
			return (NULL);
		prev->next = new;
		lst = lst->next;
		prev = prev->next;
	}
	new->next = NULL;
	return (origin);
}
