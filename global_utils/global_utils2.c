#include "global_utils.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

char	*strjoin_s(char *s, char *s2, t_bool free_)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	if (s2)
		i += ft_strlen(s2);
	str = (char *)malloc(i + 1);
	i = 0;
	j = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (free_)
		free(s);
	return (str);
}

char	*strjoin_c(char *s, char c, t_bool free_)
{
	int		i;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	str = (char *)malloc(i + 2);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	str[i] = c;
	str[++i] = '\0';
	if (free_)
		free(s);
	return (str);
}

