/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/14 18:35:53 by nhariman      ########   odam.nl         */
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

int		check_restbuf(char **line, char *restbuf)
{
	int	n_position_restbuf;

	n_position_restbuf = ft_find_newline(restbuf);
	if (n_position_restbuf == 0)
	{
		printf("newline at start, something in restbuf \n");
		restbuf = ft_substr(restbuf, 1, ft_strlen(restbuf) - 1);
		return (1);
	}
	if (n_position_restbuf != -1)
	{
		printf("something in line, something in restbuf \n");
		*line = ft_strjoin(*line, ft_substr(restbuf, 0,
				n_position_restbuf));
		restbuf = ft_substr(restbuf, n_position_restbuf + 1,
					ft_strlen(restbuf) - n_position_restbuf);
		return (1);
	}
	else
	{
		printf("nothing in restbuf \n");
		*line = ft_strjoin(*line, restbuf);
		free(restbuf);
		restbuf = NULL;
	}
	return (0);
}

int			free_buffers(char *buffer, char *restbuf)
{
	free(buffer);
	free(restbuf);
	buffer = NULL;
	restbuf = NULL;
	return (-1);
}

//if restbuf is not empty, return 1, if restbuf is empty return 0, if 1 is returned, do not read more, if error, return -1
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
			printf("newline at start, something in restbuf \n");
			restbuf = ft_substr(restbuf, 1, ft_strlen(restbuf) - 1);
			return (1);
		}
		if (n_position_restbuf != -1)
		{
			printf("something in line, something in restbuf \n");
			*line = ft_strjoin(*line, ft_substr(restbuf, 0,
					n_position_restbuf));
			restbuf = ft_substr(restbuf, n_position_restbuf + 1,
						ft_strlen(restbuf) - n_position_restbuf);
			return (1);
		}
		else
		{
			printf("nothing in restbuf \n");
			*line = ft_strjoin(*line, restbuf);
			free(restbuf);
			restbuf = NULL;
		}
	}
	while (bytes_read > 0) // put in function, use int? if 1 is returned, return 1, if 0 is returned, read again, if -1 is returned: free buf and restbuf and return -1
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

int			main(void)
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
	return (0);
}
