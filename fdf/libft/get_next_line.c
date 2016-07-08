/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aempisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 03:33:36 by aempisse          #+#    #+#             */
/*   Updated: 2014/11/14 03:33:45 by aempisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static void		gnl_memcpy(const void *dst, const void *src, int len)
{
	while (len > 7)
	{
		*((unsigned long long int*)dst) = *((unsigned long long int*)src);
		dst += 8;
		src += 8;
		len -= 8;
	}
	while (len-- > 0)
		*((unsigned char*)(dst++)) = *((unsigned char*)(src++));
}
*/

static t_gnlfd	*get_gnlfd(int const fd)
{
	static t_gnlfd	*gnlfd_list = NULL;
	t_gnlfd			*tmp;

	tmp = gnlfd_list;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if ((tmp = (t_gnlfd*)malloc(sizeof(t_gnlfd))) == NULL)
		return (NULL);
	*tmp = (t_gnlfd){NULL, fd, 0, 0, 0, gnlfd_list};
	gnlfd_list = tmp;
	return (tmp);
}

static int		buff_read(t_gnlfd *gnlfd)
{
	char			*tmp;
	int				len;

	if ((tmp = (char*)malloc(gnlfd->length + GNL_BUFF_SIZE + 1)) == NULL)
		return (-1);
	ft_memcpy(tmp, gnlfd->buff, gnlfd->length);
	if (gnlfd->buff != NULL)
		free(gnlfd->buff - gnlfd->offset);
	gnlfd->buff = tmp;
	len = read(gnlfd->fd, tmp + gnlfd->length, GNL_BUFF_SIZE);
	tmp[gnlfd->length + GNL_BUFF_SIZE] = '\0';
	gnlfd->length += (len < 0) ? 0 : len;
	gnlfd->offset = 0;
	gnlfd->i = 0;
	return (len);
}

static int		buff_cut(t_gnlfd *gnlfd, int len, t_buff *dst, int rem)
{
	gnlfd->buff[len] = '\0';
	dst->data = gnlfd->buff;
	dst->length = len;
	dst->i = 0;
	len += rem;
	gnlfd->offset += len;
	gnlfd->buff += len;
	gnlfd->length -= len;
	gnlfd->i -= len;
	return (1);
}

int				get_next_line(int fd, t_buff *line)
{
	t_gnlfd			*gnl;
	int				len;

	if (fd >= 0 && line != NULL && (gnl = get_gnlfd(fd)) != NULL)
		while (1)
		{
			gnl->i--;
			while (++(gnl->i) < gnl->length)
				if (gnl->buff[gnl->i] == '\n' || gnl->buff[gnl->i] == -1)
					return (buff_cut(gnl, gnl->i, line, 1));
			if ((len = buff_read(gnl)) < 0)
				break ;
			if (len == 0 && gnl->length == 0)
				return (*line = (t_buff){(NULL), 0, 0}, free(gnl->buff - gnl->offset),
				*gnl = (t_gnlfd){NULL, fd, 0, 0, 0, gnl->next}, 0);
			if (len == 0)
				return (buff_cut(gnl, gnl->length, line, 0));
		}
	return (-1);
}
