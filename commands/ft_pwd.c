#include "ft_builtin.h"

int	ft_pwd(int ac, char **av)
{
	char	pwd[1025];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	return (0);
}
