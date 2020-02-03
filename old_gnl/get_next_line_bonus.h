/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 17:19:55 by nhariman       #+#    #+#                */
/*   Updated: 2020/01/29 17:43:16 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
