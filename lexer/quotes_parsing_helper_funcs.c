#include "../include/lexer.h"
#include "../include/ft_variables.h"
#include "../include/minishell.h"

void	handle_double_quotes(t_lexer *l, char **s, int *i, int *s_index)
{
	int	pos;

	pos = l->position;
	read_and_parse_double_quoted(l, s, s_index);
	(*i) += (l->position - pos);
}

void	handle_single_quote(t_lexer *l, char **s, int *i, int *s_index)
{
	int	pos;

	check_quotes_errors(l, l->ch);
	pos = l->position;
	read_single_quoted(l, l->ch, s, s_index);
	(*i) += (l->position - pos);
}

void	init_parse_quoted_vars(t_lexer *l, char quote, char **s, int **infos)
{
	(*s) = ft_malloc(2024);
	ft_bzero((*s), 2024);
	(*infos) = has_next_quote(l, quote);
}

void	handle_alphanum_identifier(t_lexer *l, char **s, int *i, int *s_index)
{
	int		pos;
	char	*idt;

	pos = l->position;
	idt = read_identifier(l, 0);
	(*s) = strjoin_s((*s), idt, true);
	(*i) += (l->position - pos);
	(*s_index) += (l->position - pos);
	free(idt);
}

void	handle_evn_vars_with_no_quotes(t_lexer *l, char **s, int *i)
{
	char	*env_value;

	if (ft_isdigit(l->ch))
	{
		next_char(l);
		return ;
	}
	if (l->ch == '~')
		env_value = get_var(g_config.envp, "HOME");
	else
	{
		env_value = get_env_value(l);
		if (env_value == NULL)
			return ;
	}
	(*s) = strjoin_s(*s, env_value, true);
	(*i) += (int) ft_strlen(env_value);
}
