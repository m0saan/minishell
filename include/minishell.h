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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "node.h"
# include "lexer.h"
# include "parser.h"
# include "error.h"
# include "ft_vector.h"
# include "ft_types.h"
# include "ft_variables.h"
# include "ft_builtin.h"

# define IS_LAST 2
# define IS_FIRST 0
# define IS_MIDDLE 1
# define IS_FIRSTLAST 3

typedef struct s_redir
{
	t_type		type;
	char		*arg;
}					t_redir;

typedef struct s_cmd
{
	char		*argv[1024];
	t_vector	*redirs;
	int			count;
}					t_cmd;

typedef struct s_minishell
{
	t_vector	*envp;
	t_bool		is_forked;
	int			status;
	char		*prompt;
	t_vector	*x_malloc_vec;
}					t_minishell;

extern t_minishell	g_config;

int			exec_cmd(t_cmd *cmd);
t_bool		is_builtin(char *cmd);
void		run_cmds(t_vector *cmds);
int			fill_envp(char **envp);
t_redir		*create_redir(enum e_val_type type, char *arg);
void		free_token(t_token *tok);
void		slice_str(const char *str, char *buffer, size_t start, size_t end);
void		read_single_quoted(t_lexer *l, char quote, char **s, int *index);
t_node		*init_and_fill_redirs(t_node *child, t_cmd *tmp_cmd, t_type type);
t_bool		is_redir(const t_node *child);
t_node		*handle_all_redirs(t_node *child, t_cmd *tmp_cmd);
void		signal_handler_parent(int sig);
t_error		*check_first_token(t_parser *p);
void		fill_out_env_command(t_cmd *tmp_cmd, const char *tmp);
t_vector	*fill_out_vector_with_commands(t_node *ast_node);
void		parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd);
void		handle_errors(t_cmd *cmd, t_bool ispath, int errno_);
void		update_status_code(int code);
char		**extract_envp(t_vector *g_env);
void		close_pipes(int fd[][2], int pos, int index);
void		setup_pipes(int fd[][2], int position, int index);
int			get_position(t_size size, int index);
void		restore_stdinout(int sout, int sin);
int			setup_all_redirs(t_vector *redirs, int *sout, int *sin);
t_vector	*get_paths(char *path_str, char *cmd);
t_bool		is_path(char *cmd);
t_cmd		*create_cmd(void);
void		delete_redir(void *redir);
void		delete_cmd(void *cmd);
int			save_stdinout(int *sout, int *sin);
void		free_syntax_tree(t_node *ast_node);
void		ft_init(char **env, int ac, char **av);
void		start(char *line);

#endif