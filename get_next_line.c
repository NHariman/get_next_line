/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/19 17:08:17 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/28 20:46:10 by nhariman      ########   odam.nl         */
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
	while (str && str[i] != '\0')
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

	gnl.bytes_read = 1;
	while (gnl.bytes_read > 0)
	{
		gnl.bytes_read = read(gnl.fd, buf, BUFFER_SIZE);
		if (gnl.bytes_read < 0)
			return (NULL);
		buf[gnl.bytes_read] = '\0';
		gnl.line_read = ft_strjoin(gnl.line_read, buf);
		if (!gnl.line_read)
			return (NULL);
		if (find_newline(buf) > -1)
			break ;
	}
	return (gnl.line_read);
}

int			fill_line(t_gnl gnl, char **line)
{
	int		newline;
	size_t	remainder;

	newline = find_newline(gnl.line_read);
	remainder = 0;
	if (newline != -1)
	{
		if (newline != 0)
			*line = ft_substr(gnl.line_read, 0, newline);
		else
			*line = ft_strdup("");
		remainder = 1;
	}
	else
		*line = ft_strdup(gnl.line_read);
	if (!*line)
		return (-1);
	return (newline != -1 && remainder ? 1 : 0);
}

char		*fill_leftover(char *str)
{
	int		newline;
	char	*leftover;

	newline = find_newline(str);
	if (newline != -1)
	{
		leftover = ft_substr(str, newline + 1, ft_strlen(str) - newline - 1);
		if (!leftover)
			return (NULL);
	}
	else
		return (NULL);
	return (leftover);
}

int			get_next_line(int fd, char **line)
{
	static char		*leftover;
	t_gnl			gnl;
	int				ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	gnl.line_read = NULL;
	gnl.fd = fd;
	*line = gnl.line_read;
	if (leftover)
	{
		gnl.line_read = ft_strdup(leftover);
		free(leftover);
		leftover = NULL;
	}
	if (find_newline(gnl.line_read) == -1)
		gnl.line_read = read_line(gnl);
	if (!gnl.line_read)
		return (-1);
	ret = fill_line(gnl, line);
	leftover = fill_leftover(gnl.line_read);
	free(gnl.line_read);
	return ((find_newline(gnl.line_read) != -1 && !leftover) ? -1 : ret);
}

///* 
int			main(void)
{
	int		fd;
//	int		fd2;
	char	*line;
	int		i;
//	int		j;
//	int		gnl;

	fd = open("test.txt", O_RDONLY);
	i = 1;
//	j = 0;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
//		gnl = get_next_line(fd, &line);
		printf("OUTPUT OF GNL: %d | %s\n", i, line);
//		printf("OUTPUT OF GNL: %d | %s\n", gnl, line);
		free(line);
//		i++;
	}
	line = NULL;
	while (1) {;}
	close(fd);
	/*
	close(fd);
	fd2 = open("test.txt", O_RDONLY);
	i = get_next_line(fd2, NULL);
	printf("OUTPUT OF GNL, LINE IS NULL: %d\n", i);
	printf("TESTING WITH OPENING AND TRYING TO READ AFTER FILE ENDED\n\n");
	while (j < 50)
	{
		gnl = get_next_line(fd2, &line);
		printf("OUTPUT OF GNL: %d | %s\n", gnl, line);
		free(line);
		j++;
	} */
	return (0);
} 
//*/