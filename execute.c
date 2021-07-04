/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:25:17 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/03 21:48:41 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility/ft_utility.h"
#include "global_utils/global_utils.h"
#include "minishell.h"



int		get_position(t_size size, int index)
{
	if (size == 1)
		return (IS_FIRSTLAST);
	if (index == 0)
		return (IS_FIRST);
	if (index == ((int)size - 1))
		return (IS_LAST);
	return (IS_MIDDLE);
}

int		setup_redirection(t_type type, char *arg, int *sout, int *sin)
{
	int fd;

	if (type == RIGHT)
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == RIGHT_APPEND)
		fd = open(arg, O_CREAT | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == HEREDOC) {
		fd = open_heredoc(arg);
	}
	else if (type == LEFT)
		fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (p_error(arg, NULL, NULL, 1));
	if (type == RIGHT || type == RIGHT_APPEND)
	{
		*sout = dup(1);
		dup2(fd, 1);
		close(fd);
	}
	else if (type == LEFT || type == HEREDOC)
	{
		*sin = dup(0);
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

void	restore_redirs(int sout, int sin)
{
	if (sout != -1)
	{
		dup2(sout, 1);
		close(sout);
	}
	if (sin != -1)
	{
		dup2(sin, 0);
		close(sin);
	}
}

int		setup_all_redirs(t_vector *redirs, int *sout, int *sin)
{
	int i;
	int code;
	t_redir *redir;

	i = -1;
	code = 0;
	while (++i < (int)redirs->size)
	{
		restore_redirs(*sout, *sin);
		redir = (t_redir *) at(redirs, i);
		if (setup_redirection(redir->type, redir->arg, sout, sin) != 0)
			code = 1;
		free(redir->arg);
	}
	return (code);
}

void	setup_pipes(int fd[][2], int position, int index)
{
	const int prev_idx = index - 1;

	if (position == IS_FIRST)
	{
		dup2(fd[index][1], 1);
		close(fd[index][0]);
	}
	else if (position == IS_MIDDLE)
	{
		dup2(fd[prev_idx][0], 0);
		dup2(fd[index][1], 1);
		close(fd[index][0]);
		close(fd[prev_idx][1]);
	}
	else if (position == IS_LAST)
	{
		dup2(fd[prev_idx][0], 0);
		close(fd[prev_idx][1]);
		close(fd[index][1]);
		close(fd[index][0]);
	}
	close(fd[index][1]);
	close(fd[index][0]);
}

void	close_pipes(int fd[][2], int pos, int index)
{
	if (pos == IS_FIRST)
		close(fd[index][1]);
	if (pos == IS_MIDDLE)
	{
		close(fd[index - 1][0]);
		close(fd[index][1]);
	}
	if (pos == IS_LAST)
		close(fd[index - 1][0]);
}

int		run_cmd_parent(t_cmd *cmd)
{
	//dprintf(2, "run_cmd_parent\n");
	int	sout;
	int sin;
	int	code;

	sout = -1;
	sin = -1;
	code = 0;
	if (cmd->redirs != NULL && !is_empty(cmd->redirs))
		if (setup_all_redirs(cmd->redirs, &sout, &sin) != 0)
			code = 1;
	if (code == 0)
	{
		//dprintf(2, "run_cmd_parent -> exec_cmd\n");
		code = exec_cmd(cmd);
	}
	// update_status_code(code);
	restore_redirs(sout, sin);
	// unlink("/tmp/.HEREDOC");
	return (code);
}

pid_t	run_cmd_child(t_cmd *cmd, int fd[][2], t_size size, int index)
{
	pid_t pid;
	int pos;
	int sout;
	int sin;

	sin = -1;
	sout = -1;
	if ((pid = fork()) < 0)
		exit(1);
	g_is_forked = true;
	pos = get_position(size, index);
	if (pid == 0)
	{
		setup_pipes(fd, pos, index);
		if (cmd->redirs != NULL && !is_empty(cmd->redirs))
			if (setup_all_redirs(cmd->redirs, &sout, &sin) != 0)
				 exit(1);
		exit(exec_cmd(cmd));
	}
	// unlink("/tmp/.HEREDOC");
	close_pipes(fd, pos, index);
	return pid;
}

void	update_status_code(int code)
{
	if (code >= 0)
		set_var2(g_envp, "?", ft_itoa(code), false);
	else
		set_var2(g_envp, "?", ft_itoa(WEXITSTATUS(g_status)), false);
}

void	run_single_builtin(t_vector *cmds)
{
	// dprintf(2, "run_single_builtin\n");
	t_cmd	*cmd;

	cmd = (t_cmd *) at(cmds, 0);
	update_status_code(run_cmd_parent(cmd));
	// delete(cmds);
}

void 	run_multiple_cmds(t_vector *cmds)
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
	while (++i < cmds->size)
		if (pids[i] > 0)
			waitpid(pids[i], &g_status, 0);
	update_status_code(-1);
}

void	run_cmds(t_vector *cmds)
{
	// dprintf(2, "run_cmds\n");
	t_cmd	*cmd;

	cmd = (t_cmd *) at(cmds, 0);
	if (cmds->size == 1 && (cmd->count == 0 || is_builtin(cmd->argv[0])))
	{
		// dprintf(2, "run_cmds -> run_single_builtin\n");
		run_single_builtin(cmds);
	}
	else
	{
		run_multiple_cmds(cmds);
	}
	g_is_forked = false;
}

