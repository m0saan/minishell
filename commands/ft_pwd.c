#include "ft_buildin.h"

int		ft_pwd(int ac, char *av)
{
	printf("%s\n", get_var(g_envp, "PWD"));
	return (0);
}