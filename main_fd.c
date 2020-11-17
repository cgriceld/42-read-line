#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		res;
	char	*line;

	fd = open("test_files/line=buff.txt", O_RDONLY);
	while ((res = get_next_line(fd, &line)) == 1)
	{
		printf("%d\n", res);
		printf("[%s]\n", line);
		free(line);
	}
	printf("%d\n", res);
	printf("[%s]\n", line);
	free(line);

	close(fd);
	return (0);
}