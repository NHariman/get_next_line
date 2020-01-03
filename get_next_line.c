/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/03 21:23:59 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*check_restbuf(char **line, char *restbuf)
{
	ft_strjoin(**line, restbuf);
	free(restbuf);
	return (line);
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
	int			i;

	bytes_read = 1;
	if (!line || fd < 0)
		return (-1);
	*line = ft_strdup("");
	if (restbuf)
		check_restbuf(*line, restbuf);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		while (buffer[i] != '\n' || buffer[i] != '/0')
			i++;
		if (buffer[i] == '\n')
		{
			line = ft_strjoin(**line, ft_substr(buffer, 0, i));
			restbuf = ft_substr(buffer, i + 1, (i - BUFFER_SIZE - 1));
			break ;
		}
		else
			ft_strjoin(*line, buffer);
	}
	if (!*line)
		free_buffers(buffer, restbuf);
	return (bytes_read);
}

int		main(void)
{
	int	fd;
	int i;
	char **line;

	fd = fopen(test.txt, "r");
	i = 1;
	while (i)
	{
		i = get_next_line(fd, **line);
		printf("%s/n", *line);
		printf("%d", i);
	}
	return (0);
}
