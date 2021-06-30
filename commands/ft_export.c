#include "ft_builtin.h"

int	print_var(t_var *var)
{
	int	i;

	i = -1;
	write(1, "declare -x ", 11);
	write(1, var->key, strlen(var->key));
	if (var->value)
	{
		write(1, "=\"", 2);
		while (var->value[++i])
		{
			if (var->value[i] == '$')
				write(1, "\\", 1);
			write(1, &var->value[i], 1);
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
	return (0);
}

int	add_vars(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		set_var(g_envp, av[i]);
	return (0);
}

int	ft_export(int ac, char **av)
{
	if (ac == 1)
		list_vars(g_envp, false, print_var);
	else if (ac > 1)
	{
		add_vars(ac, av);
	}
	return (0);
}
