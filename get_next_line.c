/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2019/12/16 20:11:59 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			read_first_line(char *buffer, char *restbuf, char **line)
{
	int i;

	i = 0;
	while (buffer[i] != '\0' || buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' && !restbuf)
	{
		*line = ft_substr(buffer, 0, i);
		restbuf = ft_substr(buffer, i + 1, (i - BUFFER_SIZE - 1));
	}
	if (buffer[i] == '\0')
		*line = ft_stdrup(buffer);
	if (!*line || !restbuf)
		return (free_buffers(buffer, restbuf));
	return (1);
}

int			free_buffers(char *buffer, char *restbuf)
{
	free(buffer);
	free(restbuf);
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	size_t		bytes_read;
	char		*buffer;
	static char	*restbuf;

	if (!line || fd < 0)
		return (-1);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	buffer[BUFFER_SIZE] = '\0';
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free_buffers);
	if (bytes_read > 0)
	{
		if (!restbuf)
			read_first_line(buffer, restbuf, line);
		else
		{
			/* stuff happens here */
		}
	}
	return (bytes_read);
}

int	main(void)
{
	int	fd;
	int i;
	char *line;

	fd = fopen(test.txt, "r");
	while (1)
	{
		i = get_next_line(fd, line);
		printf("%d", i);
	}
	return (0);
}
