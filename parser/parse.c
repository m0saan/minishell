#include "../include/minishell.h"
#include "../include/parser.h"

t_error	*catch_errors(t_parser *p, t_error *error)
{
	if (p->cur_token->type == ILLEGAL || p->peek_token->type == ILLEGAL)
	{
		set_error(error, "Illegal Syntax!");
		exit(EXIT_FAILURE);
	}
	if (p->cur_token->type == RIGHT || p->cur_token->type == LEFT
		|| p->cur_token->type == RIGHT_APPEND)
	{
		if (!expect_peek(p, *p->lexer, ARG))
			set_error(error, ERR1);
	}
	else if (p->cur_token->type == PIPE)
	{
		if (expect_peek(p, *p->lexer, PIPE))
			set_error(error, ERR1);
	}
	else if (p->cur_token->type == SEMICOLON)
	{
		if (expect_peek(p, *p->lexer, SEMICOLON))
			set_error(error, ERR1);
	}
	return (error);
}

void	replace_token(t_parser *p)
{
	if (p->cur_token->type == TILDE)
		p->cur_token->literal = get_var(g_envp, "HOME");
}

t_node	*parse_command(t_node *ast_node, t_parser *p)
{
	t_error	*error;
	t_node	*arg;

	ast_node = new_node(NODE_COMMAND);
	error = malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	while (p->cur_token->type != END_O_F)
	{
		replace_token(p);
		catch_errors(p, error);
		if (catch_errors(p, error)->is_error)
		{
			printf("%s \n", error->error_msg);
			return (NULL);
		}
		arg = new_node(NODE_ARG);
		set_node_val_str(arg, p->cur_token->literal, p->cur_token->type);
		add_child_node(ast_node, arg);
		free_token(p->cur_token);
		next_token_p(p);
	}
	return (ast_node);
}

void	free_token(t_token *tok)
{
	if (tok->literal)
		free(tok->literal);
	free(tok);
}
