#include "../include/minishell.h"

t_token_t	lookup_type(char *ident)
{
	const char	*commands[7] = {"echo", "cd", "pwd",
								  "export", "unset", "env", "exit"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(ident, commands[i]) == 0)
			return (COMMAND);
	}
	return (ARG);
}

t_token	*new_token(t_token_t token_type, char ch, t_token *token)
{
	token->letter_literal = ch;
	if (token_type == TILDE && peek_char(token->lexer) != 0)
	{
		next_char(token->lexer);
		token->literal = handle_identifier_with_no_quotes(token->lexer, token)->literal;
	}
	else
		token->literal = NULL;
	token->type = token_type;
	return (token);
}
