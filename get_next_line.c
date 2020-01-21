/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/19 17:08:17 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/21 17:04:27 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int			find_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char		*read_line(t_gnl gnl)
{
	char	buf[BUFFER_SIZE + 1];

	while (gnl.bytes_read > 0)
	{
		gnl.bytes_read = read(gnl.fd, buf, BUFFER_SIZE);
		buf[gnl.bytes_read] = '\0';
		gnl.line_read = ft_strjoin(gnl.line_read, buf);
		if (find_newline(buf) > -1)
			break ;
		if (!gnl.line_read)
			break ;
	}
	return (gnl.line_read);
}

int			fill_line(t_gnl gnl, char **line, char *leftover)
{
	int		newline;

	newline = find_newline(gnl.line_read);
	if (newline != -1)
	{
		if (newline != 0)
			*line = ft_substr(gnl.line_read, 0, newline);
		leftover = ft_substr(gnl.line_read, newline + 1,
					ft_strlen(gnl.line_read) - newline - 1);
		if (!leftover)
			return (-1);
	}
	else
		*line = ft_strdup(gnl.line_read);
	return (newline != -1 && leftover && gnl.bytes_read != 0 ? 1 : 0);
}

int			get_next_line(int fd, char **line)
{
	static char		*leftover;
	t_gnl			gnl;
	int				ret;
	int				newline;

	gnl.line_read = ft_strdup("");
	gnl.fd = fd;
	gnl.bytes_read = 1;
	*line = ft_strdup("");
	if (leftover)
	{
		gnl.line_read = ft_strjoin(gnl.line_read, leftover);
		free(leftover);
		leftover = NULL;
	}
	if (find_newline(gnl.line_read) == -1)
		gnl.line_read = read_line(gnl);
	if (!gnl.line_read)
		return (-1);
	ret = fill_line(gnl, line, leftover);
	newline = find_newline(gnl.line_read);
	if (newline != -1)
		leftover = ft_substr(gnl.line_read, newline + 1,
					ft_strlen(gnl.line_read) - newline - 1);
	return (ret);
}

int			main(void)
{
	int		fd;
	char	*line;
	int		i;
//	int		gnl;

	fd = open("test.txt", O_RDONLY);
	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
//		gnl = get_next_line(fd, &line);
		printf("OUTPUT OF GNL: %d | %s\n", i, line);
//		printf("OUTPUT OF GNL: %d | %s\n", gnl, line);
		free(line);
//		i++;
	}
	return (0);
} 
