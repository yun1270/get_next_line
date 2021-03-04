/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujung <yujung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:10:08 by yujung            #+#    #+#             */
/*   Updated: 2021/03/03 01:04:59 by yujung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int		rt_val(char **line, char **buf, char *bn)
{
	char *temp;

	if (bn != 0)
	{
		*line = ft_substr(*buf, 0, bn - *buf);
		temp = ft_strdup(bn + 1);
		free(*buf);
		*buf = temp;
		return (1);
	}
	if (*buf != 0)
	{
		*line = *buf;
		*buf = NULL;
	}
	else
		*line = NULL;
	return (0);
}

int				get_next_line(int fd, char **line)
{
	int			rd;
	char		*buff;
	static char	*buf[OPEN_MAX];
	char		*temp;
	char		*bn;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (buf[fd] == 0)
		buf[fd] = ft_strdup("");
	while (!(bn = ft_strchr(buf[fd], '\n'))
		&& (rd = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd] = 0;
		temp = ft_strjoin(buf[fd], buff);
		free(buf[fd]);
		buf[fd] = temp;
	}
	if (rd < 0)
		return (-1);
	return (rt_val(line, &buf[fd], bn));
}
