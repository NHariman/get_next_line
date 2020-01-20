/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/19 17:08:17 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/20 22:57:18 by nhariman      ########   odam.nl         */
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

char		*read_line(int fd, char *str)
{
	int		bytes_read;
	char	buf[BUFFER_SIZE + 1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		str = ft_strjoin(str, buf);
		if (find_newline(buf) > -1)
		{
//			printf("read_line, found newline break:\n %s\n", str);
			break ;
		}
		if (!str)
			break ;
	}
	return (str);
}

int			fill_line(char *str, char **line, char *leftover)
{
	int		newline;

	newline = find_newline(str);
	if (newline != -1)
	{
		if (newline != 0)
			*line = ft_substr(str, 0, newline);
		leftover = ft_substr(str, newline + 1, ft_strlen(str) - newline - 1);
		if (!leftover)
			return (-1);
//		printf("FILL_LINE if statement:\n LINE: %s\nLEFTOVER: %s\n\n", *line, leftover);
	}
	else
	{
		*line = ft_strdup(str);
//		printf("FILL_LINE else statement:\n %s\n\n", *line);
	}
	return (newline != -1 && leftover ? 1 : 0);
}
// if fails: struct can be static
int			get_next_line(int fd, char **line)
{
	static char		*leftover;
	char			*str;
	int				ret;
	int				newline;

	str = ft_strdup("");
	*line = ft_strdup("");
	if (!leftover)
	{
//		printf("gnl if statement used\n");
		str = read_line(fd, str);
		if (!str)
			return (-1);
		ret = fill_line(str, line, leftover);
	}
	else
	{
//		printf("gnl else statement used\n");
		str = ft_strjoin(str, leftover);
		free(leftover);
		leftover = NULL;
		ret = fill_line(str, line, leftover);
//		printf("GNL, print LINE from else statement:\n LINE: %s\nLEFTOVER: %s\n", *line, leftover);
	}
	newline = find_newline(str);
	if (newline != -1)
		leftover = ft_substr(str, newline + 1, ft_strlen(str) - newline - 1);
//	printf("GNL, print LINE:\n LINE: %s\nLEFTOVER: %s\n", *line, leftover);
	return (ret);
}

/* 
int			main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	i = get_next_line(fd, &line);
	printf("%d | %s\n", i, line);
//	free(line);
	return (0);
} */


int			main(void)
{
	int		fd;
	char	*line;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 1;
	while (i == 1)
	{
		i = get_next_line(fd, &line);
		printf("OUTPUT OF GNL: %d | %s\n", i, line);
		free(line);
//		i++;
	}
	return (0);
} 
