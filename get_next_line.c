#include <fcntl.h> // for open
#include <stdio.h> // for printf

#include "get_next_line.h"

/*
** Reads and writes to line one string (before the first \n) from fd.
** Params: file descriptor for reading, value of what has been read.
** Return:
** 1 - line has been read;
** 0 - EOF has been reached;
** -1 - an error happened;
*/

int	get_next_line(int fd, char **line)
{
	
}


int	main(int argc, char **argv)
{
	int 	fd;
	int 	flag;
	char 	*line;
	
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return;
	while ((flag = get_next_line(fd, &line)) == 1)
	{
		printf("%d\n", flag);
		printf("%s\n", line);
		free(line);
	}
	printf("%d\n", flag);
	printf("%s\n", line);
		
	free(line);
	close(fd);
	return (0);
}

/*
int open(const char *pathname, int flags) in <fcntl.h>

opens the file specified in pathname and return a fd (small, nonnegative integer, entry in the
system-wide table of open files) that corresponds the file.
The argument flags must include one of the following access modes:
O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file read-
only, write-only, or read/write, respectively.

ssize_t read(int fd, void *buf, size_t count) in <unistd.h>

ssize_t type - signed size_t, in <sys/types.h>. Used for a count of bytes or an error indication.
From -1 to SSIZE_MAX (in <limits.h>, limit on the number of bytes that can be read or written in a single operation).
Writes count bytes from fd to buf. If count = 0, then returns 0 and ends. If count > SSIZE_MAX, then underfined.
Returns number of read bytes. If return < count, then we may be nearly the end of file.
Moves the pointer in the file forward by the number of bytes read (continue reading from the first unread byte).
buf should be (count + 1) size.
*/