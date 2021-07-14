#include "../include/lexer.h"

void	handle_double_quotes_identifier(t_lexer *l, t_token *tok)
{
	if (check_quotes_errors(l, l->ch))
		tok->type = ILLEGAL;
	else
	{
		tok->literal = parse_quoted(l, l->ch, 0, 0);
		if (!tok->literal)
			tok->type = ILLEGAL;
		else
			tok->type = ARG;
	}
}

t_bool	check_quotes_errors(const t_lexer *l, char ch)
{
	int	i;
	int	counter;

	i = l->position;
	counter = 1;
	while (++i < l->len)
	{
		if (l->input[i] == ch)
			++counter;
	}
	if (counter % 2 != 0)
		return (true);
	return (false);
}

void	handle_single_quote_identifier(t_lexer *l, t_token *tok)
{
	check_quotes_errors(l, l->ch);
	if (tok->type == ILLEGAL)
		return;
	tok->literal = parse_quoted(l, l->ch, 0, 0);
	if (!tok->literal)
		tok->type = ILLEGAL;
	else
		tok->type = ARG;
}

t_token	*handle_right_redir(t_lexer *l, t_token *tok)
{
	if (peek_char(l) == '>')
	{
		next_char(l);
		tok = new_token(RIGHT_APPEND, 'r', tok);
	}
	else if (peek_char(l) == '<')
	{
		next_char(l);
		tok = new_token(HEREDOC, 'h', tok);
	}
	else
	{
		if (l->ch == '>')
			tok = new_token(RIGHT, l->ch, tok);
		else
			tok = new_token(LEFT, l->ch, tok);
	}
	return (tok);
}


// echo '''''''''''''''''''' bonjour