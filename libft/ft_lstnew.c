/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 22:26:54 by aempisse          #+#    #+#             */
/*   Updated: 2014/12/03 22:26:56 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*newlist;

	if ((newlist = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	newlist->content = (void*)content;
	newlist->content_size = (content == NULL) ? 0 : content_size;
	newlist->next = NULL;
	return (newlist);
}
