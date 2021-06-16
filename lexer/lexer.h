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

typedef enum e_val_type
{
	none = -2,
	VAL_STR = -1,
	left = 0,
	right = 1,
	right_append = 2,
	_pipe = 3,
	env_var = 4,
	command = 5,
	arg = 6,
	illegal = 7,
	end_of,
	semicolon,
	single_quote,
	dollar_sign,
	tilde,
}			t_type;

typedef enum e_val_type	t_token_type;

typedef struct s_lexer
{
	char	*input;
	int		position;
	int		read_position;
	char	ch;
	int		len;
	t_bool	is_error;
}				t_lexer;

typedef struct s_token
{
	t_token_type	type;
	char			*literal;
	t_lexer			*lexer;
}				t_token;

t_bool	has_closing_quote(const char *line, int i, char quote);
char	*get_env_value(t_lexer *l);
void	read_and_parse_double_quoted(t_lexer *l, char *s, int *index,
			t_error *err);
char	*parse_quoted(t_lexer *l, char quote);
t_bool	is_quote(const t_lexer *l);

#endif
