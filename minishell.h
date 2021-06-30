#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "ast/node.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "errors/error.h"
# include "utility/ft_vector.h"
# include "utility/ft_types.h"
# include "utility/ft_env.h"
# include "commands/ft_builtin.h"

# define IS_LAST 2
# define IS_FIRST 0
# define IS_MIDDLE 1
# define IS_FIRSTLAST 3

typedef struct	s_redir
{
	t_type		type;
	char		*arg;
}				t_redir;

typedef struct	s_cmd
{
	char		*argv[256];
	t_vector	*redirs;
	int			count;
}				t_cmd;

t_vector		*g_envp;
t_bool			g_is_forked;

void			ft_exit(char *msg, int code);
int				exec_cmd(t_cmd *cmd);
t_bool			is_builtin(char *cmd);
void			run_cmds(t_vector *cmds);
int				fill_envp(char **envp);
void			next_char(t_lexer *lexer);
char			peek_char(t_lexer *lexer);
void			skip_white_spaces(t_lexer *lexer);
t_token			*next_token(t_lexer *l);
t_lexer			*new_lexer(const char *line, int cmd_length);
t_token			*new_token(t_token_type token_type, char ch, t_token *token);
t_token_type	lookup_type(char *ident);
t_node			*parse_command(t_node *ast_node, t_parser *p);
void			parse_and_execute(t_lexer *lexer);
void			free_token(t_token *tok);
t_redir			*create_redir(enum e_val_type type, char *arg);
void			slice_str(const char *str, char *buffer, size_t start, size_t end);
const char		*getTypeName(enum e_val_type type);
void			read_single_quoted(t_lexer *l, char quote, char *s, int *index);
char			*to_string(void *item);
void			signal_handler(int sig);
void			fill_out_env_command(t_cmd *tmp_cmd, const char *tmp);
void			parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd);
t_node			*init_and_fill_redirs(t_node *child, t_cmd *tmp_cmd, t_type type);
t_bool			is_redir(const t_node *child);
t_node			*handle_all_redirs(t_node *child, t_cmd *tmp_cmd);
void	signal_handler_parent(int sig);
t_error	*check_first_token(t_parser *p);
void	fill_out_env_command(t_cmd *tmp_cmd, const char *tmp);
void	parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd);

#endif