#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <stdio.h>
# include "error.h"
# include "lexer.h"
# include "../include/node.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*cur_token;
	t_token	*peek_token;
}			t_parser;

t_bool		peek_token_is(t_parser *p, t_token_t t);
t_bool		expect_peek(t_parser *p, t_lexer l, t_token_t t);
void		next_token_p(t_parser *p);
t_parser	*new_parser(t_lexer *l);
t_error		*catch_errors(t_parser *p, t_error *error);
t_node		*parse_command(t_node *ast_node, t_parser *p);
int			parse_and_execute(t_lexer *lexer);

#endif
