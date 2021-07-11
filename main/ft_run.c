/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:22:21 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/11 20:07:23 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

extern t_minishell	g_config;

int	run_cmd_parent(t_cmd *cmd)
{
	int	sout;
	int	sin;
	int	code;

	sout = -1;
	sin = -1;
	code = 0;
	save_stdinout(&sout, &sin);
	if (cmd->redirs != NULL && !is_empty(cmd->redirs))
		if (setup_all_redirs(cmd->redirs, &sout, &sin) != 0)
			code = 1;
	if (code == 0)
		code = exec_cmd(cmd);
	restore_stdinout(NONE, &sout, &sin);
	return (code);
}

pid_t	run_cmd_child(t_cmd *cmd, int fd[][2], t_size size, int index)
{
	pid_t	pid;
	int		pos;
	int		sout;
	int		sin;

	sin = -1;
	sout = -1;
	pid = fork();
	if (pid < 0)
		exit(1);
	g_config.is_forked = true;
	pos = get_position(size, index);
	if (pid == 0)
	{
		save_stdinout(&sout, &sin);
		setup_pipes(fd, pos, index);
		if (cmd->redirs != NULL && !is_empty(cmd->redirs))
			if (setup_all_redirs(cmd->redirs, &sout, &sin) != 0)
				 exit(1);
		exit(exec_cmd(cmd));
	}
	close_pipes(fd, pos, index);
	return (pid);
}

void	run_single_builtin(t_vector *cmds)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) at(cmds, 0);
	update_status_code(run_cmd_parent(cmd));
}

void	run_multiple_cmds(t_vector *cmds)
{
	int		i;
	int		fd[1024][2];
	pid_t	pids[1024];
	t_cmd	*cmd;

	i = -1;
	while (++i < (int)cmds->size)
	{
		pipe(fd[i]);
		cmd = (t_cmd *)at(cmds, i);
		pids[i] = run_cmd_child(cmd, fd, cmds->size, i);
	}
	i = -1;
	while (++i < (int)cmds->size)
		if (pids[i] > 0)
			waitpid(pids[i], &g_config.status, 0);
	update_status_code(-1);
}

void	run_cmds(t_vector *cmds)
{
	int		i;
	t_cmd	*cmd;

	init_heredoc(cmds);
	cmd = (t_cmd *) at(cmds, 0);
	if (cmds->size == 1 && (cmd->count == 0 || is_builtin(cmd->argv[0])))
		run_single_builtin(cmds);
	else
		run_multiple_cmds(cmds);
	delete_free(cmds, &delete_cmd);
	i = -1;
	if (g_config.heredoc )
	while (++i < (int)g_config.heredoc->size)
		unlink((char *)at(g_config.heredoc, i));
	delete_free(g_config.heredoc, &free);
	g_config.is_forked = false;
}

void	init_heredoc(t_vector *cmds)
{
	int		i;
	int		j;
	int		index;
	char	*fname;
	t_cmd	*cmd;
	
	i = -1;
	index = 0;
	g_config.hereindex = 0;
	g_config.heredoc = new_vector_s(10);
	while (cmds && ++i < (int)cmds->size)
	{
		cmd = (t_cmd *)at(cmds, i);
		j = -1;
		while (cmd && cmd->redirs && ++j < (int)cmd->redirs->size)
		{
			if (((t_redir *)at(cmd->redirs, j))->type == HEREDOC)
			{
				fname = strjoin_c("/tmp/.HEREDOC", index++ + 48, false); 
				waitpid(open_heredoc(fname, ((t_redir *)at(cmd->redirs, j))->arg), NULL, 0);
				insert(g_config.heredoc, fname);
			}
		}
	}
	i = -1;
	while (++i < g_config.heredoc->size)
	{
		dprintf(2, "F: %s\n", (char *)at(g_config.heredoc, i));
	}
	
}
