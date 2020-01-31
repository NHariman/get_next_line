/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 20:04:41 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/31 19:57:38 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

typedef struct	s_gnl
{
	int			bytes_read;
	int			fd;
	char		*line_read;
	int			newline;
}				t_gnl;

char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2);
int				get_next_line(int fd, char **line);

#endif
