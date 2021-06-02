/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:25:17 by ehakam            #+#    #+#             */
/*   Updated: 2021/06/02 16:43:08 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_envp(char **envp)
{
	int		i;
	int		shlvlv;
	t_var	*shlvl_var;

	i = -1;
	if (!envp)
		return (1);
	g_envp = new_vector();
	while (envp[++i] != NULL)
		g_envp->insert(g_envp, split_key_value_v(envp[i]));
	g_envp->insert(g_envp, new_var_kv("?", "0"));
	shlvl_var = get_var_2(g_envp, "SHLVL");
	if (shlvl_var != NULL && shlvl_var->value != NULL) {
		shlvlv = atoi(shlvl_var->value);
		shlvlv++;
		// covert back to string and insert in shlvl_var
		set_var2(g_envp, "SHLVL", ft_itoa(shlvlv));
	}
	return (0);
}

char *to_string(void *item)
{
	char *it = (char *)item;
	return (strcat(it, "\n"));
}

int get_position(t_size size, int index)
{
	if (size == 1)
		return (IS_FIRSTLAST);
	if (index == 0)
		return (IS_FIRST);
	if (index == size - 1)
		return (IS_LAST);
	return (IS_MIDDLE);
}

void setup_redirection(t_type type, char *arg, int *sout, int *sin)
{
	int flags;
	int fd;

	if (type == right)
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == right_append)
		fd = open(arg, O_CREAT | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == left)
		fd = open(arg, O_RDONLY);
	if (fd < 0)
		exit(1);
	if (type == right || type == right_append)
	{
		*sout = dup(1);
		dup2(fd, 1);
	}
	else if (type == left)
	{
		*sin = dup(0);
		dup2(fd, 0);
	}
}

void restore_redirs(int sout, int sin)
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

void setup_all_redirs(t_vector *redirs, int *sout, int *sin)
{
	int i;
	t_redir *redir;

	i = -1;
	while (++i < redirs->size)
	{
		restore_redirs(*sout, *sin);
		redir = (t_redir *)redirs->at(redirs, i);
		setup_redirection(redir->type, redir->arg, sout, sin);
		free(redir->arg);
	}
}

void setup_pipes(int fd[][2], int position, int index)
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
		close(fd[prev_idx][1]);
	}
	else if (position == IS_LAST)
	{
		dup2(fd[prev_idx][0], 0);
		close(fd[index][1]);
		close(fd[index][0]);
		close(fd[prev_idx][1]);
	}
}

void close_pipes(int fd[][2], int pos, int index)
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

pid_t run_cmd_parent(t_cmd *cmd)
{
	int	sout;
	int sin;

	sout = -1;
	sin = -1;
	if (cmd->redirs != NULL && !is_empty(cmd->redirs))
		setup_all_redirs(cmd->redirs, &sout, &sin);
	exec_cmd(cmd);
	// Set $? Accordingly
	restore_redirs(sout, sin);
	return -1;
}

pid_t run_cmd_child(t_cmd *cmd, int fd[][2], t_size size, int index)
{
	pid_t pid;
	int pos;
	int sout;
	int sin;

	sin = -1;
	sout = -1;
	if ((pid = fork()) < 0)
		ft_exit("Error\nFORK FAILED!", -1);
	g_is_forked = true;
	pos = get_position(size, index);
	if (pid == 0)
	{
		setup_pipes(fd, pos, index);
		if (cmd->redirs != NULL && !is_empty(cmd->redirs))
			setup_all_redirs(cmd->redirs, &sout, &sin);
		exit(exec_cmd(cmd));
	}
	close_pipes(fd, pos, index);
	return pid;
}

void  run_cmds(t_vector *cmds)
{
	int i;
	int fd[1024][2];
	pid_t pids[1024];
	t_cmd	*cmd;

	i = -1;
	cmd = (t_cmd *)cmds->at(cmds, 0);
	if (cmds->size == 1 && is_builtin(cmd->argv[0]))
	{
		pids[0] = run_cmd_parent(cmd);
	}
	else
	{
		while (++i < cmds->size)
		{
			pipe(fd[i]);
			t_cmd *cmd = (t_cmd *)cmds->at(cmds, i);
			pids[i] = run_cmd_child(cmd, fd, cmds->size, i);
		}
	}
	i = -1;
	while (++i < cmds->size)
		if (pids[i] > 0)
			wait(&pids[i]);
	g_is_forked = false;
}

/*
** HELPER FUNC
*/
t_redir *create_redir(t_type type, char *arg)
{
	t_redir *r = malloc(sizeof(t_redir));
	r->arg = strdup(arg);
	r->type = type;
	return (r);
}

