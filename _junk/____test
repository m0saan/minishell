#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum s_bool
{
	false = 0,
	true = 1/* data */
}				t_bool;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*strjoin_c(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

char	*ft_substr2(char *str, int from, int to)
{
	int		i;
	int		len;
	char	*sub;

	i = 0;
	if (!str)
		return (NULL);
	len = (int) ft_strlen(str);
	if (from < 0 || from >= to || from >= len || to > len)
		return (NULL);
	sub = (char *)malloc((to - from + 1) * sizeof(char));
	while (from < to)
		sub[i++] = str[from++];
	sub[i] = '\0';
	return (sub);
}

char	*replace_var(char *buffer)
{
	t_bool	is_var;
	int		i;
	int		start;
	int		end;
	char	*new_buff = NULL;
	char	*key;

	i = 0;
	is_var = false;
	while (buffer[i])
	{
		if (buffer[i] == '$' && buffer[i + 1] != ' ' && buffer[i + 1])
			is_var = true;
		if (!is_var && buffer[i] != '\0')
		{
			new_buff = strjoin_c(new_buff, buffer[i]);
			i++;
			continue ;
		}
		start = ++i;

		if (buffer[i] >= '0' && buffer[i] <= '9')
		{
			if (buffer[i] == '0')
				new_buff = strjoin_c(new_buff, '@');
			++i;
		}
		else if ((buffer[i] >= 'a' && buffer[i] <= 'z')
					|| (buffer[i] >= 'A' && buffer[i] <= 'Z'))
		{
			end = start;
			while (buffer[end] && ((buffer[i] >= 'a' && buffer[i] <= 'z')
					|| (buffer[i] >= 'A' && buffer[i] <= 'Z')
					|| (buffer[i] >= '0' && buffer[i] <= '9')
					|| buffer[end] == '_'))
				++end;
			key = ft_substr2(&buffer[start], start, end);
			if (key)
				new_buff = strjoin_c(new_buff, '+');
			i = end;
		}
	}
	//free(buffer);
	return (new_buff);
}


int main(int ac, char **av) {
	char *str = replace_var(av[1]);
	printf("STR |%s|\n", str);
	return (0);
}