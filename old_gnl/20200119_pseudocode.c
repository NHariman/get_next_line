/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:50 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/16 19:01:28 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// static int	proto_fn(int fd, char **line)
// {
// 	int		bytes_read;
// 	int		n_position;
// 	char	buf[BUFFER_SIZE + 1];
// 	char	*temp;

// 	bytes_read = read(fd, buf, BUFFER_SIZE);
// 	buf[bytes_read] = '\0';
// 	n_position = ft_find_newline(buf);
// 	if (n_position == -1)
// 	{
// 		temp = ft_strjoin(*line, buf);
// 		free (*line);
// 		return (proto_fn(fd, temp));
// 	}
// 	else
// 	{
// 		*line = ft_strjoin(*line, ft_substr(buf, 0, n_position));
		 
// 	}
	
// }

static int	*get_line(const int fd, char **line)
{
	char	*swap;
	int		bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0)
		return (0);
	if (ft_find_newline(buf))
		//
	else
	{
		swap = ft_strjoin(prev, buf);
		free(*line);
		*line = swap;
		return (get_line(fd, swap))
	}
}

static int	get_line(t_gnl *gnl)
{
	char	buf[BUFFER_SIZE + 1];
	char	*swap;

	gnl->bytes_read = read(gnl->fd, buf, BUFFER_SIZE);
	buf[gnl->bytes_read] = '\0';
	if (gnl->line_read)
	{
		swap = ft_strjoin(gnl->line_read, buf);
		free(gnl->line_read);
		gnl->line_read = swap;
	}
	else
		gnl->line_read = buf;
	gnl->linebreak = find_linebreak(gnl->line_read);
	if (gnl->linebreak)
		return (0);
	else
		return (get_line(gnl));
}

int			get_next_line(int fd, char **line)
{
	static char	*leftover;
	t_gnl		gnl;
	
	gnl.line_read = 	
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
