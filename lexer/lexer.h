/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 20:33:21 by moboustt          #+#    #+#             */
/*   Updated: 2021/06/16 20:33:23 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>
# include "../utility/ft_types.h"
# include "../errors/error.h"
# include "../global_utils/global_utils.h"

typedef enum e_val_type
{
	NONE = -2,
	LEFT = 0,
	RIGHT,
	RIGHT_APPEND,
	PIPE,
	ENV_VAR,
	COMMAND,
	ARG,
	ILLEGAL,
	HEREDOC,
	END_O_F,
	SEMICOLON,
	TILDE,
}			t_type;

typedef enum e_val_type	t_token_type;

typedef struct s_lexer
{
	char	*input;
	int		position;
	int		read_position;
	char	ch;
	int		len;
}				t_lexer;

typedef struct s_token
{
	t_token_type	type;
	char			*literal;
	t_lexer			*lexer;
}				t_token;

char		*get_env_value(t_lexer *l);
void		read_and_parse_double_quoted(t_lexer *l, char *s, int *index);
t_bool		is_quote(const t_lexer *l);
t_lexer		*new_lexer(const char *line, int cmd_length);
void		skip_white_spaces(t_lexer *l);
char		peek_char(t_lexer *l);
void		next_char(t_lexer *lexer);
enum e_bool	has_char(char c);
enum e_bool	is_letter(char ch);
int			*has_next_quote(t_lexer *l, char quote);
void		slice_str(const char *str, char *buffer, size_t start, size_t end);
void		read_single_quoted(t_lexer *l, char quote, char *s, int *index);
char		*parse_quoted(t_lexer *l, char quote, 	int	i, int s_index);
void		handle_alphanum_identifier(t_lexer *l, char **s, int *i,
				int *s_index);
void		init_parse_quoted_vars(t_lexer *l, char quote,
				char **s, int **infos);
char		*read_identifier(t_lexer *l, int i);
void		handle_single_quote(t_lexer *l, char *s, int *i, int *s_index);
void		handle_double_quotes(t_lexer *l, char *s, int *i, int *s_index);
t_bool		is_quote(const t_lexer *l);
size_t		get_env_var_last_index(t_lexer *l);
char		*get_env_value(t_lexer *l);
int			get_env_var_end(t_string str);
char		*handle_env_variables(t_string str, int i, int k);
void		parse_and_get_env_value(char *str, char *env_name,
				int *i, char **env_value);
t_token		*handle_right_redir(t_lexer *l, t_token *tok);
void		handle_single_quote_identifier(t_lexer *l, t_token *tok);
void		handle_double_quotes_identifier(t_lexer *l, t_token *tok);
t_token		*handle_identifier_with_no_quotes(t_lexer *l, t_token *tok);
t_token		*handle_dollar_token(t_lexer *l, t_token *tok);
t_token		*handle_eof_token(t_token *tok);
t_token		*handle_illegal_token(const t_lexer *l, t_token *tok);
t_bool		check_quotes_errors(const t_lexer *l, char ch);
void		handle_evn_vars_with_no_quotes(t_lexer *l, char **s, int *i);

#endif
