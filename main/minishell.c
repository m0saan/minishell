#include "../include/minishell.h"

void	update_status_code(int code)
{
	if (code >= 0)
		set_var2(g_envp, "?", ft_itoa(code), false);
	else
		set_var2(g_envp, "?", ft_itoa(WEXITSTATUS(g_status)), false);
}

void	signal_handler_parent(int sig)
{
	const char	*prompt = "minishell-0.1$ ";

	if (sig == SIGQUIT && g_is_forked)
		dprintf(1, "Quit: 3");
	if (!(sig == SIGQUIT && !g_is_forked))
		dprintf(1, "\n");
	if (sig == SIGINT && !g_is_forked)
	{
		update_status_code(1);
		dprintf(1, "%s", g_prompt);
	}
}

void	parse_and_execute(t_lexer *lexer)
{
	t_cmd		*cmd;
	t_node		*ast_node;
	t_parser	*p;
	t_error		*err;

	cmd = malloc(sizeof(t_cmd));
	p = new_parser(lexer);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->redirs = new_vector();
	err = check_first_token(p);
	if (err->is_error)
	{
		printf("%s '%s'\n", err->error_msg, p->peek_token->literal);
		return ;
	}
	ast_node = parse_command(ast_node, p);
	if (ast_node == NULL)
		return ;
	run_cmds((t_vector *) fill_out_vector_with_commands(ast_node));
	t_node *head;

	head = ast_node->first_child;
	while(head)
	{
		free(head->val.str);
		head = head->next_sibling;
	}
	free(p);
}

char	*get_line(void)
{
	static char	*line_read;
	const char	*prompt = "minishell-0.1$ ";

	// rl_on_new_line();
	line_read = readline (g_prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*lexer;

	g_is_forked = false;
	fill_envp(env);
	g_prompt = strjoin_s(get_var(g_envp, "PWD"), " _$ ", false);
	signal(SIGQUIT, signal_handler_parent);
	signal(SIGINT, signal_handler_parent);
	while (true)
	{
		line = get_line();
		if (line && line[0] == '\0')
			continue ;
		if (!line)
		{
			if (isatty(0))
				write(2, "exit\n", 5);
			break ;
		}
		lexer = new_lexer(line, (int) ft_strlen(line));
		parse_and_execute(lexer);
		if (line)
			free (line);
		free(lexer);
	}
	return (atoi(get_var(g_envp, "?")));
}
