#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char    *line;
	int     fd1, fd2, res, eof1, eof2;

	fd1 = open("test_files/wool&water.txt", O_RDONLY);
	fd2 = open("test_files/empty_lines.txt", O_RDONLY);
    eof1 = 0;
    eof2 = 0;

	while (!eof1 || !eof2) 
	{
		if (!eof1)
		{
			res = get_next_line(fd1, &line);
			printf("%d\n", res);
			if (res == 1)
				printf("[%s]\n", line);
			else if (!res)
			{
				printf("[%s]", line);
				printf("First file ended\n");
				eof1++;
			}
			else if (res == -1)
				break;
			free(line);
		}
		if (!eof2)
		{
			res = get_next_line(fd2, &line);
			printf("%d\n", res);
			if (res == 1)
				printf("[%s]\n", line);
			else if (!res)
			{
				printf("[%s]", line);
				printf("Second file ended\n");
				eof2++;
			}
			else if (res == -1)
				break;
			free(line);
		}
	}
	close(fd1);
	clode(fd2);

	return (0);
}