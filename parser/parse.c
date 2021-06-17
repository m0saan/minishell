#include "../minishell.h"
#include "parser.h"

t_error *catch_errors(t_parser *p, t_error *error)
{
	if (p->cur_token->type == illegal || p->peek_token->type == illegal)
		set_error(error, "Illegal Syntax!");
	if (p->cur_token->type == right || p->cur_token->type == left || p->cur_token->type == right_append)
	{
		if (!expect_peek(p, *p->lexer, arg))
			set_error(error, ERR1);
	}
	else if (p->cur_token->type == _pipe)
	{
		if (expect_peek(p, *p->lexer, _pipe))
			set_error(error, ERR1);
	}
	else if (p->cur_token->type == semicolon)
	{
		if (expect_peek(p, *p->lexer, semicolon))
			set_error(error, ERR1);
	}
	return (error);
}

void	replace_token(t_parser *p)
{
	if (p->cur_token->type == tilde)
		p->cur_token->literal = get_var(g_envp, "HOME");
}

t_node	*parse_command(t_node *ast_node, t_parser *p)
{
	ast_node = new_node(NODE_COMMAND);
	t_error *error = malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	while (p->cur_token->type != end_of)
	{
		replace_token(p);
		catch_errors(p, error);
		if (catch_errors(p, error)->is_error)
		{
			printf("%s \n", error->error_msg);
			return (NULL);
		}
		t_node *arg = new_node(NODE_ARG);
		if (!arg)
		{
			// free node tree -> ast_node;
			// free the token -> tok;
			return (NULL);
		}
		set_node_val_str(arg, p->cur_token->literal, p->cur_token->type);
		add_child_node(ast_node, arg);
		//free_token(tok);
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