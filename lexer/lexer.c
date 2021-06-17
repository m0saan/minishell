/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:48:38 by moboustt          #+#    #+#             */
/*   Updated: 2021/06/16 20:49:58 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *next_token(t_lexer *l)
{
	t_token *tok;

	tok = malloc(sizeof(t_token));
	tok->lexer = l;
	skip_white_spaces(l);
	if(l->ch == '~')
		tok = new_token(tilde, l->ch, tok);
	else if(l->ch == ';')
		tok = new_token(semicolon, l->ch, tok);
	else if(l->ch == '<')
		tok = new_token(left, l->ch, tok);
	else if(l->ch == '>')
		tok = handle_right_redir(l, tok);
	else if(l->ch == '|')
		tok = new_token(_pipe, l->ch, tok);
	else if(l->ch == '\'')
		handle_single_quote_identifier(l, tok);
	else if(l->ch == '\"')
		handle_double_quotes_identifier(l, tok);
	else if(l->ch == '\\')
		return handle_escape_token(l, tok);
	else if(l->ch == '$')
		return handle_dollar_token(l, tok);
	else if(l->ch == 0)
		return handle_eof_token(tok);
	else if(is_letter(l->ch))
		return handle_identifier_with_no_quotes(l, tok);
	else
		return handle_illegal_token(l, tok);
	next_char(l);
	return tok;
}

void read_and_parse_double_quoted(t_lexer *l, char *s, int *index)
{
	char const to_be_escaped[] = {'$', '"', '\\'};
	char *env_name;
	next_char(l);
	while(l->ch != '"') {
		if(l->ch == '\\' && ft_strchr(to_be_escaped, peek_char(l))) {
			handle_escape_in_double_quotes(l, s, index);
			continue;
		}
		if(l->ch == '$' && ft_isalnum(l->input[l->read_position])) {
			next_char(l);
			if(ft_isdigit(l->ch)) {
				next_char(l);
				continue;
			}
			env_name = get_env_value(l);
			if(env_name == NULL)
				continue;
			s = strcat(s, env_name);
			(*index) += (int) ft_strlen(env_name);
			continue;
		}
		s[(*index)++] = l->ch;
		next_char(l);
	}
	next_char(l);
}

