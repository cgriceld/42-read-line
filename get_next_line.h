#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int	get_next_line(int fd, char **line);

/*
** Struct-node that stores the fd and string remainder.
*/
typedef struct	s_lstfd
{
    int				fd;
    char			*cashe;
    struct s_fdlst	*next;
}				t_lstfd;

#endif