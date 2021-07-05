#include "../include/minishell.h"

void	parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd)
{
	char	*tmp;

	if (child->val != NULL)
	{
		tmp = handle_env_variables(child->val, -1, 0);
		if (tmp != NULL)
			fill_out_env_command(tmp_cmd, tmp);
	}
	else
		tmp_cmd->argv[tmp_cmd->count++] = child->val;
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

t_vector	*fill_out_vector_with_commands(t_node *ast_node)
{
	t_node		*child;
	t_vector	*vector;
	t_cmd		*tmp_cmd;

	vector = new_vector();
	child = ast_node->first_child;
	tmp_cmd = create_cmd();
	while (child)
	{
		if (is_redir(child))
			child = handle_all_redirs(child, tmp_cmd);
		else if (child->val_type == PIPE)
		{
			insert(vector, tmp_cmd);
			tmp_cmd = create_cmd();
		}
		else
			tmp_cmd->argv[tmp_cmd->count++] = child->val;
		child = child->next_sibling;
	}
	insert(vector, tmp_cmd);
	return (vector);
}
