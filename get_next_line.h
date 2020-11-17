#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_lstfd
{
	int				fd;
	char			*cache;
	struct s_lstfd	*next;
}					t_lstfd;

int					get_next_line(int fd, char **line);
int					lstdelone(t_lstfd **head, const int fd);
char				*nchr(const char *s);
int					subc(char **cache, char *n);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s1, char *s2);

#endif
