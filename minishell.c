#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	ft_memset(command, 0, sizeof(t_cmd));
	command->redirs = new_vector();
	return (command);
}

t_vector	*fill_out_vector_with_commands(t_node *ast_node)
{
	t_node		*child;
	t_vector	*vector;
	t_cmd		*tmp_cmd;

	vector = new_vector();
	child = ast_node->first_child;
	tmp_cmd = create_cmd();
	while (child)
	{
		if (is_redir(child))
			child = handle_all_redirs(child, tmp_cmd);
		else if (child->val_type == PIPE)
		{
			insert(vector, tmp_cmd);
			tmp_cmd = create_cmd();
		}
		else
			tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
		child = child->next_sibling;
	}
	insert(vector, tmp_cmd);
	return (vector);
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
	line_read = readline (prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*lexer;

	g_is_forked = false;
	fill_envp(env);
	signal(SIGQUIT, signal_handler_parent);
	signal(SIGINT, signal_handler_parent);
	while (true)
	{
		line = get_line();
		if (line && line[0] == '\0')
			continue ;
		if (!line)
		{
			write(2, "exit\n", 5);
			break ;
			// TODO: replace with value of $?
		}
		lexer = new_lexer(line, (int) ft_strlen(line));
		parse_and_execute(lexer);
		if (line)
			free (line);
		free(lexer);
	}
	return (atoi(get_var(g_envp, "?")));
}
