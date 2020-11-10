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
    struct s_lstfd	*next;
}				t_lstfd;

/*
** Functions to read and process new line.
*/
int		get_next_line(int fd, char **line);
void	buff_read(char *buff, t_lstfd *tmp, char **line, int *flag);
void	check_cashe(t_lstfd *tmp, char **line, int *flag);

/*
** Functions to navigate through list.
*/
t_lstfd	*find_node(t_lstfd **head, const int fd);
int		del_one(t_lstfd **head, const int fd);
int		del_all(t_lstfd **head, char **line);

/*
** libft functions.
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

#endif