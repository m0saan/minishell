/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:44:58 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/12 21:52:04 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

char	*replace_var(char *buffer)
{
	char	*new_buff;
	t_bool	is_var;
	int		start;
	int		end;

	end = 0;
	new_buff = NULL;
	is_var = false;
	while (buffer[end])
	{
		if (buffer[end] == '$'
			&& (ft_isalnum(buffer[end + 1]) || ft_isspecial(buffer[end + 1])))
			is_var = true;
		if (!is_var && buffer[end] != '\0')
		{
			new_buff = strjoin_c(new_buff, buffer[end++], true);
			continue ;
		}
		start = ++end;
		end = handle_var(&new_buff, buffer, end, start);
		is_var = false;
	}
	free(buffer);
	return (new_buff);
}

t_bool	read_write(int fd, char *delim)
{
	char	*buffer;
	t_bool	exit_by_delim;

	exit_by_delim = false;
	// write(2, "> ", 2);
	while (true)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			break ;
		// if (get_next_line(&buffer) <= 0)
		// 	break ;
		if (ft_strcmp(delim, buffer) == 0)
		{
			exit_by_delim = true;
			break ;
		}
		if (buffer && buffer[0] && index_of_c(buffer, '$') != -1)
			buffer = replace_var(buffer);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		// write(2, "> ", 2);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	return (exit_by_delim);
}

pid_t	open_heredoc(char *fname, char *delim)
{
	int		fd;
	t_bool	exit_by_delim;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		g_config.is_forked = true;
		fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd < 0)
			exit(p_error(fname, NULL, NULL, 1));
		exit_by_delim = read_write(fd, delim);
		close(fd);
		if (!exit_by_delim)
			p_error("warning", "here-document delimited by end-of-file wanted",
				delim, 0);
		exit(0);
	}
	return (pid);
}

int		handle_heredoc(t_redir *redir, int index)
{
	char	*fname;

	fname = strjoin_c("/tmp/.HEREDOC", index++ + 48, false);
	signal(SIGINT, signal_handler_heredoc);
	waitpid(open_heredoc(fname, redir->arg), &g_config.status, 0);
	g_config.is_forked = false;
	signal(SIGINT, signal_handler_parent);
	if (WEXITSTATUS(g_config.status) == 1)
	{
		update_status_code(1);
		return (1);
	}
	free(redir->arg);
	redir->arg = fname;
	return (0);
}

int		init_heredoc(t_vector *cmds)
{
	int		i;
	int		j;
	int		index;
	t_cmd	*cmd;
	
	i = -1;
	index = 0;
	while (cmds && ++i < (int)cmds->size)
	{
		cmd = (t_cmd *)at(cmds, i);
		j = -1;
		while (cmd && cmd->redirs && ++j < (int)cmd->redirs->size)
		{
			if (((t_redir *)at(cmd->redirs, j))->type == HEREDOC)
			{
				if (handle_heredoc((t_redir *)at(cmd->redirs, j), index++) == 1)
					return (1);
			}
		}
	}
	return (0);
}