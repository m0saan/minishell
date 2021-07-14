#include "../include/parser.h"
#include "../include/minishell.h"

void	next_token_p(t_parser *p)
{
	p->cur_token = p->peek_token;
	p->peek_token = next_token(p->lexer);
}

t_parser	*new_parser(t_lexer *l)
{
	t_parser	*p;

	p = ft_malloc(sizeof(t_parser));
	p->lexer = l;
	next_token_p(p);
	next_token_p(p);
	return (p);
}

t_bool	peek_token_is(t_parser *p, t_token_t t)
{
	return (p->peek_token->type == t);
}

t_bool	expect_peek(t_parser *p, t_lexer l, t_token_t t)
{
	if (peek_token_is(p, t))
		return (true);
	else
		return (false);
}
