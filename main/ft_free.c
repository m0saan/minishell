#include "../include/minishell.h"

t_bool	is_valid_to_be_freed(t_type t)
{
	return (t != END_O_F && t != ILLEGAL);
}

void	free_parser(t_error *err, t_parser *p)
{
	if (p->cur_token->literal && is_valid_to_be_freed(p->cur_token->type))
		free(p->cur_token->literal);
	if (p->peek_token->literal && is_valid_to_be_freed(p->peek_token->type))
		free(p->peek_token->literal);
	free(p->cur_token);
	free(p->peek_token);
	free(err);
	free(p);
}

void	free_syntax_tree(t_node *ast_node, t_bool _free)
{
	t_node	*head;
	t_node	*to_be_freed;

	head = ast_node->first_child;
	while (head)
	{
		to_be_freed = head;
		if (_free)
			if (head->val)
				free(head->val);
		head = head->next_sibling;
		free(to_be_freed);
	}
	free(ast_node);
}
