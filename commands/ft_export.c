#include "../minishell.h"

int		predicate(void *s1, void *s2)
{
	const t_var *ss1 = (const t_var *)s1;
	const t_var *ss2 = (const t_var *)s2;
	return (strcmp(ss1->key, ss2->key));
}

// char	*create_displayable_var(t_var *var)
// {
// 	char *output;
// 	const char *prefix = "declare -x ";
// 	output = (char *)malloc((strlen(var->raw) + strlen(prefix) + 10) * sizeof(char));
// 	strcat(output, prefix);
// 	strcat(output, var->key);
// 	if (var->value)
// 	{
// 		strcat(output, "=");
// 		strcat(output, "\"");
// 		strcat(output, var->value);
// 		strcat(output, "\"");
// 	}
// 	return (output);
// }

// int		print_var(t_var *var)
// {
// 	int		i;
// 	i = -1;
// 	const char *out = create_displayable_var(var);
// 	write(1, "<", 1);
// 	while (out[++i])
// 	{
// 		if (out[i] == '$')
// 			write(1, "\\", 1);
// 		write(1, &out[i], 1);
// 	}
// 	write(1, ">", 1);
// 	write(1, "\n", 1);
// 	return (0);
// }

int		print_var(t_var *var)
{
	int		i;

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

int		list_vars()
{
	char *var_name;
	char *var_value;
	int  i;

	i = -1;
	sort(g_envp, predicate);
	while (++i < g_envp->size)
		print_var((t_var *)g_envp->at(g_envp, i));
}

int		add_vars(int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
		set_var(g_envp, av[i]);
	return (0);
}

int		fill_envp(char **envp)
{
	int		i;

	i = -1;
	if (!envp)
		return (1);
	g_envp = new_vector();
	while (envp[++i] != NULL)
		g_envp->insert(g_envp, split_key_value_v(envp[i]));
	return (0);
}

int		main(int ac, char **av, char **env)
{
	fill_envp(env);
	if (ac == 1)
		list_vars();
	else if (ac > 1) {
		add_vars(ac, av);
		list_vars();
	}
}



