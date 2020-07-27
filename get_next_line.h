/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 17:25:46 by bshang            #+#    #+#             */
/*   Updated: 2020/07/01 18:56:40 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct			s_list
{
	char				*rem;
	char				*rem_start;
	int					fd;
	struct s_list		*next;
}						t_list;

int						get_next_line(int fd, char **line);
int						cleaner(int fd, t_list **origin, char *buf, int res);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin_free(char **s1, char *s2);

#endif
