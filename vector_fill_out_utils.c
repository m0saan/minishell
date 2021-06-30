#include "minishell.h"

void	parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd)
{
	char	*tmp;

	if (child->val.str != NULL)
	{
		tmp = handle_env_variables(child->val.str, -1, 0);
		if (tmp != NULL)
			fill_out_env_command(tmp_cmd, tmp);
	}
	else
		tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
}

void	fill_out_env_command(t_cmd *tmp_cmd, const char *tmp)
{
	char	**splited_env_value;
	int		i;

	splited_env_value = ft_split(tmp, ' ');
	i = -1;
	while (splited_env_value[++i] != 0)
		tmp_cmd->argv[tmp_cmd->count++] = splited_env_value[i];
}

void	signal_handler_parent(int sig)
{
	const char	*prompt = "minishell-0.1$ ";

	if (sig == SIGQUIT && g_is_forked)
		dprintf(1, "Quit: 3");
	if (!(sig == SIGQUIT && !g_is_forked))
		dprintf(1, "\n");
	if (sig == SIGINT && !g_is_forked)
		dprintf(1, "%s", prompt);
}
