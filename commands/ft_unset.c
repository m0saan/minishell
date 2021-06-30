#include "ft_builtin.h"

int	ft_unset(int ac, char **av)
{
	int		i;
	int		code;

	if (ac == 1)
		return (0);
	i = 0;
	code = 0;
	while (av[++i])
		if (unset_var(g_envp, av[i]) != 0)
			code = 1;
	return (code);
}
