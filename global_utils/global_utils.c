#include "global_utils.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*bb;

	i = 0;
	bb = b;
	while (i < len)
	{
		bb[i] = c;
		i++;
	}
	return (bb);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
