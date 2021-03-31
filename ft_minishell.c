#include "ft_minishell.h"

int		main(int ac, char **av, char **env)
{
	int _read = 0;
	char buff[1024];

	while ((_read = read(0, buff, 1024)) > 0)
	{
		buff[_read] = '\0';
		printf("INPUT: %s", buff);
	}

	
	return (0);
}