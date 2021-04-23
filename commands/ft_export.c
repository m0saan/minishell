#include "../minishell.c"

int	list_vars()
{

}

int add_vars()
{
	
}

int ft_export(int ac, char **av)
{
	g_envp = new_vector();
	if (ac == 1)
		list_vars();
	else if (ac > 1)
		add_vars(ac, av);
}