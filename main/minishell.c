#include "../include/minishell.h"

void	update_status_code(int code)
{
	if (code >= 0)
		set_var2(g_config.envp, "?", ft_itoa(code), false);
	else
		set_var2(g_config.envp, "?", ft_itoa(WEXITSTATUS(g_config.status)), false);
}

void	signal_handler_parent(int sig)
{
	if (sig == SIGQUIT && g_config.is_forked)
		dprintf(1, "Quit: 3");
	if (!(sig == SIGQUIT && !g_config.is_forked))
		dprintf(1, "\n");
	if (sig == SIGINT && !g_config.is_forked)
	{
		update_status_code(1);
		dprintf(1, "%s", g_config.prompt);
	}
}

int parse_and_execute(t_lexer *lexer)
{
	t_node		*ast_node;
	t_error		*err;
	t_parser	*p;

	ast_node = NULL;
	p = new_parser(lexer);
	err = check_first_token(p);
	if (err->is_error)
		return (p_error("ZBBI 2", err->error_msg, p->peek_token->literal, 1));
	ast_node = parse_command(ast_node, p);
	if (ast_node == NULL)
		return (1);
	run_cmds((t_vector *) fill_out_vector_with_commands(ast_node));
	t_node *head;
	head = ast_node->first_child;
	while(head)
	{
		free(head->val.str);
		head = head->next_sibling;
	}
	free(p);
	return (0);
}

char	*get_line(void)
{
	static char	*line_read;

	line_read = readline (g_config.prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*lexer;
	int 	code;

	ac = 0;
	av = NULL;
	g_config.is_forked = false;
	fill_envp(env);
	g_config.prompt = strjoin_s(get_var(g_config.envp, "PWD"), " _$ ", false);
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
	code = atoi(get_var(g_config.envp, "?"));
	// TODO: free env
	return (code);
}
