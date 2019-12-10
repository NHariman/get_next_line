/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2019/12/10 22:54:24 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(int fd, char **line)
{
	size_t		bytes_read;
	char		*buffer;
	size_t		i;
	static char	*restbuf;

	i = 0;
	if (!line || fd < 0)
		return (-1);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	buffer[BUFFER_SIZE] = '\0';
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buffer);
		free(restbuf);
		return (-1);
	}
	if (bytes_read > 0)
	{
		while (buffer[i] != '\0' || buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n' && !restbuf)
		{
			*line = ft_substr(buffer, 0, i);
			restbuf = ft_substr(buffer, i + 1, (i - BUFFER_SIZE - 1));
		}
		if (buffer[i] == '\0')
			*line = ft_stdrup(buffer);
		return (1);
	}
	return (0);
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
