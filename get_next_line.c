#include <fcntl.h> // for open
#include <stdio.h> // for printf

#include "get_next_line.h"

#define BUFFER_SIZE 3

/*
** Reads and writes to line one string (before the first \n) from fd.
** Params: file descriptor for reading, value of what has been read.
** Return:
** 1 - line has been read;
** 0 - EOF has been reached;
** -1 - an error happened;
*/

int	del_one(t_lstfd **head, const int fd)
{
	t_lstfd *tmp;
	t_lstfd *prev;

	tmp = *head;
	while (tmp->fd != fd)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp->cashe);
	free(tmp);
	return (0);
}

/*
** 1) If head is NULL (list is empty), tries to create node with new_node function.
** 2) Try to find node with such fd, if finds, returns pointer to node,
** otherwise -- creates and appends back new node.
*/
t_lstfd	*find_node(t_lstfd **head, const int fd)
{
	t_lstfd *tmp;

	if (!*head)
	{
		*head = (t_lstfd *)malloc(sizeof(t_lstfd));
		if (!*head)
			return (NULL);
		(*head)->fd = fd;
		(*head)->cashe = NULL;
		(*head)->next = NULL;
		return (*head);
	}
	tmp = *head;
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = (t_lstfd *)malloc(sizeof(t_lstfd));
	if (!tmp->next)
			return (NULL);
	tmp = tmp->next;
	tmp->fd = fd;
	tmp->cashe = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	check_cashe(t_lstfd *tmp, char **line, int *flag)
{
	char *n;
	char *sub_cashe;

	if (!tmp->cashe)
		return ;
	if ((n = ft_strchr(tmp->cashe, '\n')))
	{
		*n++ = '\0';
		if (!(*line = ft_strdup(tmp->cashe)) || !(sub_cashe = ft_strdup(n)))
		{
			*flag = -1;
			return ;
		}
		free(tmp->cashe);
		tmp->cashe = ft_strdup(sub_cashe);
		free(sub_cashe);
		*flag = 1;
	}
}

void	buff_read(char *buff, t_lstfd *tmp, char **line, int *flag)
{
	char	*prev_cashe;
	ssize_t	bytes_read;

	while (!*flag && (bytes_read = read(tmp->fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		if (!tmp->cashe)
			tmp->cashe = ft_strdup(buff);
		else
		{
			prev_cashe = tmp->cashe;
			tmp->cashe = ft_strjoin(tmp->cashe, buff);
			free(prev_cashe);
		}
		if (!tmp->cashe)
		{
			*flag = -1;
			return ;
		}
		check_cashe(tmp, line, flag);
		if (*flag == -1)
			return;
	}
	if (bytes_read < 0)
		*flag = -1;
}

int	get_next_line(int fd, char **line)
{
	static t_lstfd	*head;
	t_lstfd			*tmp;
	char			*buff;
	int				flag;
	
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(tmp = find_node(&head, fd)))
		return (del_all(&head, NULL));
	//free(*line);
	flag = 0;
	check_cashe(tmp, line, &flag);
	if (flag)
		return (flag == 1 ? flag : del_all(&head, line));
	if (!(buff = (char *)malloc(sizeof(BUFFER_SIZE + 1))))
		return (del_all(&head, NULL));
	buff_read(buff, tmp, line, &flag);
	free(buff);
	if (flag)
		return (flag == 1 ? flag : del_all(&head, line));
	if (!(*line = ft_strdup(tmp->cashe)))
		return (del_all(&head, NULL));
	return (del_one(&head, tmp->fd));
}

int	main(void)
{
	int 	fd;
	int 	flag;
	char 	*line;
	
	fd = open("test2.txt", O_RDONLY);
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