#include "get_next_line.h"
#include <stdio.h>

static int	rt_val(char **line, char **buf, char *bn)
{
	char	*temp;

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

int	get_next_line(int fd, char **line)
{
	int			rd;
	char		*buff;
	static char	*buf[OPEN_MAX];
	char		*temp;
	char		*bn;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf[fd] == 0)
		buf[fd] = ft_strdup("");
	bn = ft_strchr(buf[fd], '\n');
	rd = read(fd, buff, BUFFER_SIZE);
	while (!bn && (rd > 0))
	{
		buff[rd] = 0;
		temp = ft_strjoin(buf[fd], buff);
		free(buf[fd]);
		buf[fd] = temp;
	}
	if (rd < 0)
		return (-1);
	free(buff);
	return (rt_val(line, &buf[fd], bn));
}
