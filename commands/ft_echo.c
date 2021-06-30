#include "ft_builtin.h"

int	ft_echo(int ac, char **av)
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
		if (i < ac - 1)
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
