/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yujung <yujung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:10:08 by yujung            #+#    #+#             */
/*   Updated: 2021/02/02 17:22:27 by yujung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void free_buf(char **p, char *temp)
{
	if (p != NULL)
	{
		free(*p);
		*p = temp;
	}
}

static void				rt_line(char **line, char **buf)
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
		free_buf(buf, temp);
		if ((*buf)[0] == '\0')
			free_buf(buf, NULL);
	}
	else
	{
		*line = ft_strdup(*buf);
		free_buf(buf, NULL);
	}
}

int return_val(int rd, int fd, char **buf)
{
	if (rd < 0)
		return (-1);
	else if (rd == 0 && buf[fd] == NULL)
		return (0);
	else
		return (1);
}

int				get_next_line(int fd, char **line)
{
	int			rd;
	char		buff[BUFFER_SIZE + 1];
	static char	*buf[256];

	if ((line == 0) || (fd < 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (buf[fd] == NULL)
			buf[fd] = "\0";
		buf[fd] = ft_strjoin(buf[fd], buff);
		if (ft_strchr(buf[fd], '\n') != 0)
			break ;
	}
	rt_line(line, &buf[fd]);
	return (return_val(rd, fd, buf));
}
