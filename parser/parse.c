#include "../include/minishell.h"
#include "../include/parser.h"

extern t_minishell	g_config;

void	free_tokens(t_parser *p, t_error *error);

t_error	*catch_errors(t_parser *p, t_error *error)
{
	if (p->cur_token->type == ILLEGAL || p->peek_token->type == ILLEGAL)
		set_error(error, "Illegal Syntax!");
	if (p->cur_token->type == RIGHT || p->cur_token->type == LEFT
		|| p->cur_token->type == RIGHT_APPEND)
	{
		if (!expect_peek(p, ARG))
			set_error(error, ERR1);
	}
	else if (p->cur_token->type == PIPE)
	{
		if (expect_peek(p, PIPE))
			set_error(error, ERR1);
	}
	if (p->cur_token->type == HEREDOC && (p->peek_token->type == LEFT
			|| p->peek_token->type == RIGHT))
		set_error(error, ERR1);
	return (error);
}

void	replace_token(t_parser *p)
{
	char	*tmp;
	char	*literal;

	if (p->cur_token->type == TILDE)
	{
		tmp = get_var(g_config.envp, "HOME");
		if (p->cur_token->literal != NULL)
		{
			literal = p->cur_token->literal;
			p->cur_token->literal = strjoin_s(tmp, \
				p->cur_token->literal, false);
			free(literal);
		}
		else
			p->cur_token->literal = ft_strdup(tmp);
	}
}

t_node	*parse_command(t_node *ast_node, t_parser *p)
{
	t_error	*error;
	t_node	*arg;

	ast_node = new_node(NODE_COMMAND);
	error = ft_malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	while (p->cur_token->type != END_O_F)
	{
		replace_token(p);
		catch_errors(p, error);
		if (catch_errors(p, error)->is_error)
		{
			p_error(NULL, error->error_msg, "Bad Token", 1);
			free(error);
			return (NULL);
		}
		arg = new_node(NODE_ARG);
		set_node_val_str(arg, p->cur_token->literal, p->cur_token->type);
		add_child_node(ast_node, arg);
		free(p->cur_token);
		next_token_p(p);
	}
	free_tokens(p, error);
	return (ast_node);
}

void	free_tokens(t_parser *p, t_error *error)
{
	free(error);
	free(p->cur_token);
	free(p->peek_token);
}
