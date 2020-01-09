/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/09 19:50:30 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char		*check_restbuf(char **line, char *restbuf)
{
	int		i;

	i = 0;
	*line = ft_strjoin(*line, restbuf);
	free(restbuf);
	return (*line);
}

int			free_buffers(char *buffer, char *restbuf, char **line)
{
	free(buffer);
	free(restbuf);
	free(*line);
	return (-1);
}


int			get_next_line(int fd, char **line)
{
	int			bytes_read;
	char		buf[BUFFER_SIZE + 1];
	static char	*restbuf;

	bytes_read = 1;
	buf[BUFFER_SIZE] = '\0';
	if (!line || fd < 0)
		return (-1);
	*line = ft_strdup("");
	if (restbuf)
		check_restbuf(line ,restbuf); 
	/* things check_restbuf has to handle:
	needs to check if there's a newline somewhere in the restbuf
	- if so, return the line until said newline, do not read more!!
	- if it finds a newline at the start: line is empty string, restbuf updates to skip one past the printed newline
	- if the restbuf does not contain a newline, put it in line and frees the buffer 
	- boolean return? if 1: return line but there's still something in restbuf do not read, 0: restbuf is empty a new read can be done
	*/
	while (bytes_read > 0)
	{
		/* create a function that reads using BUFFER_SIZE
		- find the newline, if a newline is found, at the start, line = empty string, restbuf = the rest of the content in buffer
		  !!important! this function should only be called if there are no newlines in the static restbuf!
		- if buf has no newline, put entire content in line
		- if only newline, return empty string.
		*/
	}
}

/* end of file can be found by checking if less than */
/* the BUFFER_SIZE has been read 
int			get_next_line(int fd, char **line)
{
	int			bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	static char	*restbuf;
	int			i;

	bytes_read = 1;
	buffer[BUFFER_SIZE] = '\0';
	if (!line || fd < 0)
		return (-1);
	*line = ft_strdup("");
	if (restbuf)
		check_restbuf(line, restbuf);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		i = 0;
		while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
		if (buffer[i] == '\n' && i != 0)
		{
			*line = ft_strjoin(*line, ft_substr(buffer, 0, i));
			restbuf = ft_substr(buffer, i + 1, (BUFFER_SIZE - i - 1));
			return (1);
		}
		else if (buffer[i] == '\0')
			*line = ft_strjoin(*line, buffer);
		else
			restbuf = ft_substr(buffer, 1, (BUFFER_SIZE - i - 1));
		if (bytes_read < BUFFER_SIZE)
			return (0);
		if (!*line)
		{
			free_buffers(buffer, restbuf, line);
			return (-1);
		}
	}
	return (1);
} */


int		main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 1;
	while (i)
	{
		i = get_next_line(fd, &line);
		printf("%d | %s\n", i, line);
		free(line);
	}
	close(fd);
	return (0);
}
