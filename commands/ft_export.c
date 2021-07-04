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
	int	code;

	i = 0;
	code = 0;
	while (++i < ac)
	{
		if (set_var(g_envp, av[i]) != 0)
			code = 1;
	}
	return (code);
}

int	ft_export(int ac, char **av)
{
	if (ac == 1)
		list_vars(g_envp, false, print_var);
	else if (ac > 1)
	{
		return (add_vars(ac, av));
	}
	return (0);
}
