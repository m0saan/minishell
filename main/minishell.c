/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:58:08 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/10 21:58:57 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	g_config;

void	free_syntax_tree(t_node *ast_node);

void	update_status_code(int code)
{
	char	*code_str;

	if (code >= 0)
	{
		code_str = ft_itoa(code);
		set_var2(g_config.envp, "?", code_str, false);
	}
	else
	{
		code_str = ft_itoa(WEXITSTATUS(g_config.status));
		set_var2(g_config.envp, "?", code_str, false);
	}
	if (code_str)
		free(code_str);
}

void	signal_handler_parent(int sig)
{
	if (sig == SIGQUIT && g_config.is_forked)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (sig == SIGQUIT && !g_config.is_forked)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT && g_config.is_forked)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (sig == SIGINT && !g_config.is_forked)
	{
		write(1, "\n", 1);
		// rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		update_status_code(1);
	}
}

int	parse_and_execute(t_lexer *lexer)
{
	t_node		*ast_node;
	t_error		*err;
	t_parser	*p;

	ast_node = NULL;
	// TODO: fix the following bug -> #echo helo"TTTT""#
	p = new_parser(lexer);
	err = check_first_token(p);
	if (err->is_error)
	{
		if (p->cur_token->literal)
			free(p->cur_token->literal);
		free(p->cur_token);
		free(p->peek_token);
		free(err);
		return (p_error(NULL, err->error_msg, p->peek_token->literal, 1));

	}
	ast_node = parse_command(ast_node, p);
	if (ast_node == NULL)
		return (1);
	run_cmds((t_vector *) fill_out_vector_with_commands(ast_node));
	free_syntax_tree(ast_node);
	free(p);
	return (0);
}

void	free_syntax_tree(t_node *ast_node)
{
	t_node *head;
	t_node *to_be_freed;
	head = ast_node->first_child;
	while(head)
	{
		to_be_freed = head;
		head = head->next_sibling;
		free(to_be_freed);
	}
	free(ast_node);
}

char	*get_line(void)
{
	char	*line_read;

	line_read = readline (g_config.prompt);
	if (line_read && *line_read)
		add_history (line_read);
	return (line_read);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*lexer;
	int 	code;

	ac = 0;
	av = NULL;
	code = 0;
	g_config.is_forked = false;
	fill_envp(env);
	g_config.prompt = strjoin_s(get_var(g_config.envp, "PWD"), " _$ ", false);
	signal(SIGQUIT, signal_handler_parent);
	signal(SIGINT, signal_handler_parent);
	line = NULL;
	while (true)
	{
		line = get_line();
		if (line && line[0] == '\0')
		{
			free(line);
			continue;
		}
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
