/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujung <yujung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:10:08 by yujung            #+#    #+#             */
/*   Updated: 2021/02/10 01:30:04 by yujung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int		rt_line(char **line, char **buf)
{
	int			i;
	char		*temp;

	i = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
	{
		*line = ft_substr(*buf, 0, i);
		temp = ft_strdup(&((*buf)[i + 1]));
		free(*buf);
		*buf = temp;
	}
	else
	{
		*line = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
	}
	if (*buf == NULL)
		return (0);
	return (1);
}

static int		rt_val(int rd, int fd, char **buf, char **line)
{
	if (rd == 0)
		*line = ft_strdup("");
	if (rd < 0)
		return (-1);
	else if (rd == 0 && buf[fd] == NULL)
		return (0);
	else
		return (rt_line(line, &buf[fd]));
}

int				get_next_line(int fd, char **line)
{
	int			rd;
	char		buff[BUFFER_SIZE + 1];
	static char	*buf[256];
	char		*temp;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (buf[fd] == NULL)
			buf[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(buf[fd], buff);
			free(buf[fd]);
			buf[fd] = temp;
		}
		if (ft_strchr(buf[fd], '\n') != 0)
			break ;
	}
	return (rt_val(rd, fd, buf, line));
}
