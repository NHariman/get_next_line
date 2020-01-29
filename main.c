#include "get_next_line.h"
# include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	int		fd;
	int		fd2;
	char	*line;
	int		i;
	int		j;
	int		gnl;

	fd = 0; //open("test.txt", O_RDONLY);
	i = 1;
	j = 0;
///*
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
//	while (1) {;}
	close(fd); //*/
//	/*
	fd2 = open("test.txt", O_RDONLY);
	i = get_next_line(fd2, NULL);
	printf("OUTPUT OF GNL, LINE IS NULL: %d\n", i);
	close (fd2);
	fd2 = open("test.txt", O_RDONLY);
	printf("TESTING WITH OPENING AND TRYING TO READ AFTER FILE ENDED\n\n");
	while (j < 50)
	{
		gnl = get_next_line(fd2, &line);
		printf("OUTPUT OF GNL: %d | %s\n", gnl, line);
		free(line);
		j++;
	} // */
	line = NULL;
	while (1) {;}
	close(fd2);
	return (0);
}
