#include "get_next_line.h"

int		lstdelone(t_lstfd **head, const int fd)
{
	t_lstfd *tmp;
	t_lstfd *previous;

	tmp = *head;
	if (tmp->fd == fd)
	{
		*head = tmp->next;
		if (tmp->cache)
			free(tmp->cache);
		free(tmp);
		return (0);
	}
	while (tmp->fd != fd)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	previous->next = tmp->next;
	if (tmp->cache)
		free(tmp->cache);
	free(tmp);
	return (0);
}

char	*nchr(const char *s)
{
	while (*s && *s != '\n')
		s++;
	return (*s == '\n' ? (char *)s : NULL);
}

int		subcache(char **cache, char *n)
{
	char *subcache;

	subcache = ft_strdup(n);
	if (!subcache)
		return (0);
	free(*cache);
	*cache = subcache;
	return (1);
}

char	*ft_strdup(char *s1)
{
	char *dup;
	char *tmp;

	tmp = s1;
	while (*tmp)
		tmp++;
	dup = (char *)malloc(tmp - s1 + 1);
	if (!dup)
		return (NULL);
	tmp = dup;
	while (*s1)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *join;
	char *tmp1;
	char *tmp2;

	tmp1 = s1;
	while (*tmp1)
		tmp1++;
	tmp2 = s2;
	while (*tmp2)
		tmp2++;
	join = (char *)malloc((tmp1 - s1) + (tmp2 - s2) + 1);
	if (!join)
		return (NULL);
	tmp1 = join;
	while (*s1)
		*tmp1++ = *s1++;
	while (*s2)
		*tmp1++ = *s2++;
	*tmp1 = '\0';
	return (join);
}
