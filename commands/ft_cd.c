#include "ft_builtin.h"

int	ft_cd(int ac, char **av)
{
	int		ret;
	char	pwd[1025];

	if (ac == 1)
		ret = chdir(get_var(g_envp, "HOME"));
	else if (ac >= 2)
		ret = chdir(av[1]);
	if (ret == -1)
		return (p_error("cd", av[1], NULL, 1));
	set_var2(g_envp, "OLDPWD", get_var(g_envp, "PWD"), true);
	getcwd(pwd, 1024);
	set_var2(g_envp, "PWD", pwd, true);
	return (0);
}
