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
int	del_all(t_lstfd **head, char **line);
t_lstfd	*lstfdnew(const int fd);
void	check_cache(t_lstfd *tmp, char **line, int *flag);
void	process_buff(char *buff, char **line, t_lstfd *tmp, int *flag);
int	get_next_line(int fd, char **line);
int	del_one(t_lstfd **head, const int fd);
char	*nchr(const char *s);
char	*ft_strdup(char *s1);
void	ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char *s1, char *s2);

#endif