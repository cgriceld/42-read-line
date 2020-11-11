#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>

int	del_all(t_lstfd **head, char **line)
{
	t_lstfd *tmp;

	if (*line)
		free(*line);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->cache)
			free(tmp->cache);
		free(tmp);
	}
	return (-1);
}

t_lstfd	*lstfdnew(const int fd)
{
	t_lstfd	*newnode;

	newnode = (t_lstfd *)malloc(sizeof(t_lstfd));
	if (!newnode)
		return (NULL);
	newnode->fd = fd;
	newnode->cache = NULL;
	newnode->next = NULL;
	return (newnode);
}

void	check_cache(t_lstfd *tmp, char **line, int *flag)
{
	char *n;
	char *tmpline;

	if (!(tmp->cache))
		return;
	if ((n = nchr(tmp->cache)))
	{
		*n++ = '\0';
		free(*line);
		if (!(*line = ft_strdup(tmp->cache)))
		{
			*flag = -1;
			return;
		}
		ft_strcpy(tmp->cache, n);
		*flag = 1;
		return;
	}
	tmpline = *line;
	if (!(*line = ft_strdup(tmp->cache)))
		*flag = -1;
	free(tmpline);
	free(tmp->cache);
	tmp->cache = NULL;
}

void	process_buff(char *buff, char **line, t_lstfd *tmp, int *flag)
{
	ssize_t	bytes_read;
	char	*n;
	char	*tmpline;

	check_cache(tmp, line, flag);
	while (!*flag && (bytes_read = read(tmp->fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		if ((n = nchr(buff)))
		{
			*n++ = '\0';
			if (!(tmp->cache = ft_strdup(n)))
			{
				*flag = -1;
				return;
			}
			*flag = 1;
		}
		tmpline = *line;
		if (!(*line = ft_strjoin(*line, buff)))
			*flag = -1;
		free(tmpline);
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
	if (!head && !(head = lstfdnew(fd)))
		return (-1);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (!(tmp->next) && !(tmp->next = lstfdnew(fd)))
			return (del_all(&head, NULL));
		tmp = tmp->next;
	}
	if (!(buff = (char *)malloc(BUFFER_SIZE + 1)))
		return (del_all(&head, NULL));
	flag = 0;
	*line = ft_strdup("");
	process_buff(buff, line, tmp, &flag);
	free(buff);
	if (flag)
		return (flag == 1 ? flag : del_all(&head, line));
	return (del_one(&head, tmp->fd));
}
