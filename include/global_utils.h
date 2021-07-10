#ifndef GLOBAL_UTILS_H
# define GLOBAL_UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "ft_types.h"

# define MAXVAL 9223372036854775807L
# define MINVAL 9223372036854775807L

size_t		ft_strlen(const char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_malloc(size_t size);
char		*ft_itoa(int n);
char		**ft_split(const char *ss, char c);
char		*ft_strdup(const char *s);
char		*strjoin_s(char *s, char *s2, t_bool free_);
char		*strjoin_c(char *s, char c, t_bool free_);
char		*ft_substr(char *str, int from, int to);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isspecial(int c);
int			handle_var(char **new_buf, char *buf, int idx, int start);
int			index_of_c(char *str, char c);
int			get_next_line(char **line);
int			open_heredoc(char *delim);
int			ft_atoi(char *str);
long long	ft_atol_err(char *str);

#endif
