#include "ft_builtin.h"

int	print_var2(t_var *var)
{
	if (var->value)
	{
		write(1, var->raw, strlen(var->raw));
		write(1, "\n", 1);
	}
	return (0);
}

int	ft_env(int ac, char **av)
{
	list_vars(g_envp, false, print_var2);
	return (0);
}
