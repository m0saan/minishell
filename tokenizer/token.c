#include "../include/minishell.h"

t_token_type	lookup_type(char *ident)
{
	const char	*commands[7] = {"echo", "cd", "pwd",
								  "export", "unset", "env", "exit"};
	int			i;

	i = -1;
	while (++i < 7)
	{
		if (strcmp(ident, commands[i]) == 0)
			return (COMMAND);
	}
	return (ARG);
}

t_token *new_token(t_token_type token_type, char ch, t_token *token)
{
	token->type = token_type;
	token->letter_literal = ch;
	token->literal = NULL;
	return (token);
}
