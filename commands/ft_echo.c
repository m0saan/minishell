#include "../minishell.h"

int		ft_echo(int ac, char **av)
{
	int		i;
	int		j;
	t_bool	new_line;

	i = 1;
	while (i < ac && strncmp(av[i], "-n", 2) == 0)
	{
		j = 1;
		while (av[i][j] && av[i][j] == 'n')
			j++;
		if (av[i][j] && av[i][j] != 'n')
			break ;
		i++;
	}
	new_line = i == 1;
	while (i < ac)
	{
		write(1, av[i], strlen(av[i]));
		write(1, " ", (i < ac - 1) ? 1 : 0);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
