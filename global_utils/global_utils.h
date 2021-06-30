#ifndef GLOBAL_UTILS_H
# define GLOBAL_UTILS_H

#include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
void	ft_bzero(void *s, size_t n);
char	*ft_itoa(int n);
char	**ft_split(const char *ss, char c);
char	*ft_strdup(const char *s);

# endif
