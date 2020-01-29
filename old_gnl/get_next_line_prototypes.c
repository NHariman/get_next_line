/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/11 17:26:53by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int			ft_find_newline(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char		*check_restbuf(char **line, char *restbuf)
{
	*line = ft_strjoin(*line, restbuf);
	free(restbuf);
	return (*line);
}

int			free_buffers(char *buffer, char *restbuf)
{
	free(buffer);
	free(restbuf);
	buffer = NULL;
	restbuf = NULL;
	return (-1);
}

// TO DO:
// - make a function that reads to buf
// - make function that looks for newline
// - make function that inserts stuff into line and restbuf if necessary
int			get_next_line(int fd, char **line)
{
	int				bytes_read;
	char			buf[BUFFER_SIZE + 1];
	static char		*restbuf;
	int				n_position;
	int				n_position_restbuf;

	if (!line || fd < 0)
		return (-1);
	*line = ft_strdup("");
	bytes_read = 1;
	if (restbuf)
	{
		n_position_restbuf = ft_find_newline(restbuf);
		if (n_position_restbuf == 0)
		{
//			printf("newline at start, something in restbuf \n");
			restbuf = ft_substr(restbuf, 1, ft_strlen(restbuf) - 1);
			return (1);
		}
		if (n_position_restbuf != -1)
		{
//			printf("something in line, something in restbuf \n");
			*line = ft_strjoin(*line, ft_substr(restbuf, 0,
					n_position_restbuf));
			restbuf = ft_substr(restbuf, n_position_restbuf + 1,
						ft_strlen(restbuf) - n_position_restbuf);
			return (1);
		}
		else
		{
//			printf("nothing in restbuf \n");
			*line = ft_strjoin(*line, restbuf);
			free(restbuf);
			restbuf = NULL;
		}
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		n_position = ft_find_newline(buf);
		if (n_position == 0)
		{
//			printf("read, n_position == 0");
			restbuf = ft_substr(buf, 1, bytes_read - 1);
			return (1);
		}
		if (n_position > -1)
		{
//			printf("read, newline present \n ");
			*line = ft_strjoin(*line, ft_substr(buf, 0,
					n_position));
			if (buf[n_position + 1] != '\0')
				restbuf = ft_substr(buf, n_position + 1,
							bytes_read - n_position);
			return (1);
		}
		else
		{
//			printf("read, no newline \n");
			*line = ft_strjoin(*line, buf);
		}
	}
	if (bytes_read == 0)
		return (0);
	return (-1);
}

/* 
int			get_next_line(int fd, char **line)
{
	int			bytes_read;
	char		buf[BUFFER_SIZE + 1];
	static char	*restbuf;
	int			i;

	bytes_read = 1;
	buf[BUFFER_SIZE] = '\0';
	if (!line || fd < 0)
		return (-1);
	*line = ft_strdup("");
	if (restbuf)
		check_restbuf(line ,restbuf); 
	things check_restbuf has to handle:
	needs to check if there's a newline somewhere in the restbuf
	- if so, return the line until said newline, do not read more!!
	- if it finds a newline at the start: line is empty string, restbuf updates to skip one past the printed newline
	- if the restbuf does not contain a newline, put it in line and frees the buffer 
	- boolean return? if 1: return line but there's still something in restbuf do not read, 0: restbuf is empty a new read can be done
	
	while (bytes_read > 0)
	{
		i = 0;
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (!line || fd < 0)
		create a function that reads using BUFFER_SIZE
		- find the newline, if a newline is found, at the start, line = empty string, restbuf = the rest of the content in buffer
		  !!important! this function should only be called if there are no newlines in the static restbuf!
		- if buf has no newline, put entire content in line
		- if only newline, return empty string.
		- if EOF, free restbuf
		
	}
 }  */

// end of file can be found by checking if less than
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
			return (free_buffers(buffer, restbuf, line));
	}
	return (1);
} */

/* 
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
		{
			*line = ft_strjoin_new(*line, buffer[i]);
			i++;
		}
		if (buffer[i] == '\n' && buffer[i + 1] != '\0')
			restbuf = ft_substr(buffer, i + 1, BUFFER_SIZE - i);
		if (!*line)
			return (free_buffers(buffer, restbuf, line));
		if (bytes_read < BUFFER_SIZE)
			return (0);
		else if (buffer[i] == '\n')
			return (1);
	}
	return (-1);
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
