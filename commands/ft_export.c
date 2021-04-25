#include "../minishell.c"

int  predicate(void *s1, void *s2)
{
	const char *ss1 = (const char *)s1;
	const char *ss2 = (const char *)s2;
	return (strcmp(ss1, ss2));
}


int	list_vars()
{
	char *var_name;
	char *var_value;
	int  i;

	i = -1;
	sort(g_envp, predicate);
	while (++i < g_envp->size)
	{

	}
	
}

t_bool	contains_c(const char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (true);
	return (false);
}

int		add_var(char *var)
{
	int		i;
	int		index;

	i = -1;
	index = 0;
	while (var[index] && var[index] != '=')
		index++;
	while (++i < index)
		if (contains_c("!@#$%^&)(*+-", var[i]))
			return (1);
	g_envp->insert(g_envp, strdup(var));
}

int		add_vars(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
		add_var(av[i]);
	return (0);
}

int ft_export(int ac, char **av)
{
	// g_envp = new_vector();
	if (ac == 1)
		list_vars();
	else if (ac > 1)
		add_vars(ac, av);
}