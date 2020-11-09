#include "get_next_line.h"

/*
** Creates new node with corresponding fd 
** and initializes cashe with NULL.
*/
t_lstfd	*new_node(const int fd)
{
	t_lstfd *newnode;

	newnode = (t_lstfd *)malloc(sizeof(t_lstfd));
	if (!newnode)
		return (NULL);
	newnode->fd = fd;
	newnode->cashe = NULL;
	newnode->next = NULL;
	return (newnode);
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
		return (*head = new_node(fd)); // ptr or null
	tmp = *head;
	while (tmp->next && tmp->fd != fd) // stops if find fd or reach last node
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp); // only ptr
	return (tmp->next = new_node(fd)); // ptr or null
}

/*
** Locates the position of \n in cashe if it is.
*/
char	*ft_strchr(const char *s, int c)
{
char ch;
	ch = (char)c;
while (*s && *s != ch)
		s++;
return (*s == ch ? (char *)s : NULL);
}

/*
** Сuts the required part of the string for line and cashe.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		sublen;
	char const	*substart;
	char		*substr;
	char		*tmp;

	if (!s)
		return (NULL);
	while (start-- && *s)
		s++;
	substart = s;
	while (len-- && *s)
		s++;
	sublen = s - substart;
	substr = (char *)malloc(sublen + 1);
	if (!substr)
		return (NULL);
	tmp = substr;
	while (sublen--)
		*tmp++ = *substart++;
	*tmp = '\0';
	return (substr);
}

/*
** Returns length of the string s.
*/
size_t	ft_strlen(const char *s)
{
	const char *str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}