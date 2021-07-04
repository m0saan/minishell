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

# define MAXVAL 9223372036854775807
# define MINVAL 9223372036854775808

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isspecial(int c);
void	ft_bzero(void *s, size_t n);
char	*ft_itoa(int n);
char	**ft_split(const char *ss, char c);
char	*ft_strdup(const char *s);
int		ft_atoi(char *str);

char	*strjoin_s(char *s, char *s2, t_bool free_);
char	*strjoin_c(char *s, char c, t_bool free_);

int		open_heredoc(char *delim);
int		handle_var(char **new_buf, char *buf, int idx, int start);
char	*ft_substr(char *str, int from, int to);

long long	ft_atol_err(char *str);
int		index_of_c(char *str, char c);
int	get_next_line(char **line);

# endif
