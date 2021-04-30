#include "../minishell.h"

int		ft_cd(int ac, char **av)
{
	int		ret;

	if (ac == 1)
		ret = chdir(get_var(g_envp, "HOME"));
	else if (ac >= 2)
		ret = chdir(av[1]);
	if (ret == -1)
		{
			char *err = strerror(errno);
			write(1, err, strlen(err));
			write(1, "\n", 1);
			return (ret);
		}
	set_var2(g_envp, "PWD", getenv("PWD"));
	set_var2(g_envp, "OLDPWD", getenv("OLDPWD"));
	return (ret);
}