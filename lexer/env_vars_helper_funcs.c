#include "../include/lexer.h"
#include "../include/minishell.h"

extern t_minishell g_config;

void	parse_and_get_env_value(char *str, char *env_name,
			int *i, char **env_value)
{
	size_t	end;

	(*env_value) = get_var(g_config.envp, env_name);
	(*i)++;
	end = get_env_var_end(&str[(*i)]) + (*i);
	slice_str(str, env_name, (*i), end);
}
