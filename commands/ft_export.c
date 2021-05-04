#include "ft_buildin.h"


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

char	**extract_envp(t_vector *env)
{
	int			i;
	char		**envp;
	t_vector	*extracted_v;

	i = -1;
	extracted_v = new_vector_s(env->size + 1);
	while (++i < env->size)
		extracted_v->insert(extracted_v, ((t_var *)env->at(env, i))->raw);
	envp = extracted_v->data;
	free(extracted_v);
	return (envp);
}

int		ft_export(int ac, char **av)
{
	if (ac == 1)
		list_vars(g_envp, true, print_var);
	else if (ac > 1)
	{
		add_vars(ac, av);
	}
}



