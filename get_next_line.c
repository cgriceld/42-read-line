#include <fcntl.h> // for open
#include <stdio.h> // for printf

#include "get_next_line.h"

#define BUFFER_SIZE 21

/*
** Reads and writes to line one string (before the first \n) from fd.
** Params: file descriptor for reading, value of what has been read.
** Return:
** 1 - line has been read;
** 0 - EOF has been reached;
** -1 - an error happened;
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	tmp = join;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (join);
}

int	buff_read(const int fd, t_lstfd **tmp, char **line)
{
	char	*buff;
	char	*prev_cashe;
	ssize_t	bytes_read;
	int		cashe_flag;

	while (bytes_read = read(fd, buff, BUFFER_SIZE))
	{
		if (!(buff = (char *)malloc(sizeof(BUFFER_SIZE + 1))))
			return (-1);
		if (bytes_read < 0)
			return (-1);
		buff[bytes_read] = '\0';
		prev_cashe = (*tmp)->cashe; // correct if no cashe, cashe = null, correct strjoin
		(*tmp)->cashe = ft_strjoin((*tmp)->cashe, buff);
		free(prev_cashe);
		free(buff);
		if (!((*tmp)->cashe))
			return (-1);
		if ((cashe_flag = check_cashe(&tmp, line)) == -1)
			return (-1);
		if (cashe_flag)
			return (1);
	}
	return (0);
}

int	check_cashe(t_lstfd **tmp, char **line)
{
	char *n;
	char *sub_cashe;

	if (!*tmp)
		return (0); // no cashe at all
	if ((n = ft_strchr((*tmp)->cashe, '\n'))) // ptr or null
	{
		*n = '\0';
		*line = ft_substr((*tmp)->cashe, 0, n - (*tmp)->cashe);
		if (!line)
			return (-1);
		n++;
		sub_cashe = ft_substr(n, 0, ft_strlen(n));
		if (!sub_cashe)
			return (-1);
		free((*tmp)->cashe);
		(*tmp)->cashe = sub_cashe;
		return (1);
	}
	return (0);
}


int	get_next_line(int fd, char **line)
{
	static t_lstfd	*head; // init with NULL
	t_lstfd			*tmp;
	int				cashe_flag;
	int				buff_flag;
	

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(tmp = find_node(&head, fd))) // & because if null, will alloc memory
		return (-1);
	if ((cashe_flag = check_cashe(&tmp, line)) == -1)
		return (-1);
	if (cashe_flag) // find line in cash, no need to read
		return (1);
	if ((buff_flag = buff_read(fd, &tmp, line)) == -1)
		return (-1);
	if (buff_flag) // find line in cash, no need to read
		return (1);
	
}
// free list when return (0);
// when free line?

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