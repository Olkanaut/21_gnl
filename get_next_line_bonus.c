/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:26:00 by bshang            #+#    #+#             */
/*   Updated: 2020/07/01 19:33:06 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*check_rem(t_list *temp, char **line)
{
	char	*p;

	p = NULL;
	if (temp->rem)
	{
		if ((p = ft_strchr(temp->rem, '\n')))
		{
			*p = '\0';
			*line = ft_strdup(temp->rem);
			temp->rem = ++p;
		}
		else
		{
			*line = ft_strdup(temp->rem);
			free(temp->rem_start);
			temp->rem = NULL;
			temp->rem_start = NULL;
		}
		return (p);
	}
	*line = ft_strdup("");
	return (p);
}

static int		find_write(char **p, char **buf, t_list *temp, char **line)
{
	if ((*p = ft_strchr(*buf, '\n')))
	{
		**p = '\0';
		if (!(temp->rem = ft_strdup(++(*p))))
			return (-1);
		temp->rem_start = temp->rem;
	}
	if (!(*line = ft_strjoin_free(line, *buf)))
		return (-1);
	return (0);
}

static int		proc(t_list *tmp, char **line, long long bs, t_list **origin)
{
	char		*buf;
	long long	seen;
	char		*p;

	if (!(buf = (char*)malloc(bs + 1)))
		return (cleaner(tmp->fd, origin, buf, -1));
	p = check_rem(tmp, line);
	seen = 0;
	if (!(*line))
		return (cleaner(tmp->fd, origin, buf, -1));
	while (!p && !(tmp->rem) && (seen = read(tmp->fd, buf, bs)))
	{
		if (seen < 0)
			return (cleaner(tmp->fd, origin, buf, -1));
		buf[seen] = '\0';
		if (find_write(&p, &buf, tmp, line) == -1)
			return (cleaner(tmp->fd, origin, buf, -1));
	}
	if ((seen < bs) && !(tmp->rem))
		return (cleaner(tmp->fd, origin, buf, 0));
	free(buf);
	return (1);
}

static t_list	*new_list_elem(int fd)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new->fd = fd;
	new->rem = NULL;
	new->rem_start = NULL;
	new->next = NULL;
	return (new);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*origin;
	t_list			*temp;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (origin == NULL)
		if (!(origin = new_list_elem(fd)))
			return (-1);
	temp = origin;
	while ((temp->fd != fd) && (temp->next))
		temp = temp->next;
	if (temp->fd != fd)
	{
		if (!(temp->next = new_list_elem(fd)))
			return (-1);
		temp = temp->next;
	}
	return (proc(temp, line, BUFFER_SIZE, &origin));
}
