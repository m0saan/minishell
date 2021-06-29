#include "lexer.h"
#include "../minishell.h"

void handle_double_quotes_identifier(t_lexer *l, t_token *tok)
{
	// tok = new_token(DOUBLE_QUOTE, l->ch, tok);
	check_quotes_errors(l, l->ch);

	tok->literal = parse_quoted(l, l->ch, 0, 0);
	if(!tok->literal)
		tok->type = illegal;
	else
		tok->type = arg;
}

void check_quotes_errors(const t_lexer *l, char ch) {
	int i;

	i = l->position;
	int counter = 1;
	while(++i < l->len)
	{
		if (l->input[i] == '\\' && l->input[i+1] == ch)
			i += 2;
		if (l->input[i] == ch)
			++counter;
	}
	if (counter % 2 != 0)
		ft_exit("ERROR: illegal syntax <quotes>\n", EXIT_FAILURE);
}

void handle_single_quote_identifier(t_lexer *l, t_token *tok)
{
	// tok = new_token(single_quote, l->ch, tok);
	check_quotes_errors(l, l->ch);
	tok->literal = parse_quoted(l, l->ch, 0, 0);
	if(!tok->literal)
		tok->type = illegal;
	else
		tok->type = arg;
}

t_token *handle_right_redir(t_lexer *l, t_token *tok)
{
	if(peek_char(l) == '>')
	{
		next_char(l);
		tok = new_token(right_append, 'r', tok);
	}
	else
		tok = new_token(right, l->ch, tok);
	return tok;
}

void handle_escape_in_double_quotes(t_lexer *l, char *s, int *index)
{
	next_char(l);
	s[*index] = l->ch;
	(*index) += 1;
	next_char(l);
}