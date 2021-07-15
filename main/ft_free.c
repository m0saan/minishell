#include "../include/minishell.h"

void	free_parser(t_error *err, t_parser *p)
{
	if (p->cur_token->literal)
		free(p->cur_token->literal);
	free(p->cur_token);
	free(p->peek_token);
	free(err);
	free(p);
}

void	free_syntax_tree(t_node *ast_node)
{
	t_node	*head;
	t_node	*to_be_freed;

	head = ast_node->first_child;
	while (head)
	{
		to_be_freed = head;
		head = head->next_sibling;
		free(to_be_freed);
	}
	free(ast_node);
}
