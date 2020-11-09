#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

/*
** Struct-node that stores the fd and string remainder.
** fd is used during search to find appropriate node.
** cashe contains corresponding remainder.
*/
typedef struct	s_lstfd
{
    int				fd;
    char			*cashe;
    struct s_fdlst	*next;
}				t_lstfd;

/*
** Functions to read line.
*/
int     get_next_line(int fd, char **line);
char    *ft_strchr(const char *s, int c);
int     check_cashe(t_lstfd **tmp, char **line);

/*
** Functions to navigate through list.
*/
t_lstfd	*new_node(const int fd);
t_lstfd	*find_node(t_lstfd **head, const int fd);

#endif