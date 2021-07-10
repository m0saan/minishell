#include "../include/minishell.h"

t_redir *create_redir(t_type type, char *arg)
{
	t_redir *r = ft_malloc(sizeof(t_redir));
	r->arg = arg;
	r->type = type;
	return (r);
}

t_node	*handle_all_redirs(t_node *child, t_cmd *tmp_cmd)
{
	if (child->val_type == RIGHT)
		child = init_and_fill_redirs(child, tmp_cmd, RIGHT);
	else if (child->val_type == LEFT)
		child = init_and_fill_redirs(child, tmp_cmd, LEFT);
	else if (child->val_type == RIGHT_APPEND)
		child = init_and_fill_redirs(child, tmp_cmd, RIGHT_APPEND);
	else if (child->val_type == HEREDOC)
		child = init_and_fill_redirs(child, tmp_cmd, HEREDOC);
	else if (child->val[0] == '$' && child->val_type == ENV_VAR)
		parse_env_vars_not_in_quotes(child, tmp_cmd);
	return (child);
}

t_bool	is_redir(const t_node *child)
{
	return (child->val_type == RIGHT || child->val_type == LEFT || \
			child->val_type == RIGHT_APPEND || child->val_type == HEREDOC);
}

t_node	*init_and_fill_redirs(t_node *child, t_cmd *tmp_cmd, t_type type)
{
	t_redir	*tmp;

	tmp = create_redir(type, child->next_sibling->val);
	child = child->next_sibling;
	insert(tmp_cmd->redirs, tmp);
	return (child);
}

t_error	*check_first_token(t_parser *p)
{
	const t_type	types[] = {ILLEGAL, END_O_F,
							   	SEMICOLON, PIPE, RIGHT, LEFT, RIGHT_APPEND, HEREDOC};
	t_error			*error;
	int				i;

	error = ft_malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	i = -1;
	while (++i < 8)
	{
		if ((p->cur_token->type == types[i] &&
			p->peek_token->type == END_O_F) ||
			p->cur_token->type == END_O_F ||
			p->peek_token->type == ILLEGAL)
			set_error(error, ERR1);
	}
	return (error);
}
