#include "ft_buildin.h"

int		print_var(t_var *var)
{
	if (var->value)
	{
		write(1, var->raw, strlen(var->raw));
		write(1, "\n", 1);
		// while (var->value[++i])
		// {
		// 	if (var->value[i] == '$')
		// 		write(1, "\\", 1);
		// 	write(1, &var->value[i], 1);
		// }
		// write(1, "\"", 1);
	}
	return (0);
}

int		ft_env(int ac, char **av)
{
	list_vars(g_envp, false, print_var);
	return (0);
}