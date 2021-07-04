#include "../include/lexer.h"

void	handle_double_quotes(t_lexer *l, char *s, int *i, int *s_index)
{
	int	pos;

	pos = l->position;
	read_and_parse_double_quoted(l, s, s_index);
	(*i) += (l->position - pos);
}

void	handle_single_quote(t_lexer *l, char *s, int *i, int *s_index)
{
	int	pos;

	check_quotes_errors(l, l->ch);
	pos = l->position;
	read_single_quoted(l, l->ch, s, s_index);
	(*i) += (l->position - pos);
}

void	init_parse_quoted_vars(t_lexer *l, char quote, char **s, int **infos)
{
	(*s) = malloc(1024);
	ft_bzero((*s), 1024);
	(*infos) = has_next_quote(l, quote);
}

void	handle_alphanum_identifier(t_lexer *l, char **s, int *i, int *s_index)
{
	int	pos;

	pos = l->position;
	(*s) = strcat((*s), read_identifier(l, 0));
	(*i) += (l->position - pos);
	(*s_index) += (l->position - pos);
}

void	handle_evn_vars_with_no_quotes(t_lexer *l, char **s, int *i)
{
	char	*env_name;

	if (ft_isdigit(l->ch))
	{
		next_char(l);
		return ;
	}
	env_name = get_env_value(l);
	if (env_name == NULL)
		return ;
	(*s) = strcat((*s), env_name);
	(*i) += (int) ft_strlen(env_name);
}
