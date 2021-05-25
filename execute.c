/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:25:17 by ehakam            #+#    #+#             */
/*   Updated: 2021/05/25 18:44:19 by ehakam           ###   ########.fr       */
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
	else
	{
		dprintf(2, "CHILD: DUP(NONE)\n");
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
		dprintf(2, "INFO: Exec BuiltIn in Parent\n");
		pids[0] = run_cmd_parent(cmd);
	}
	else
	{
		while (++i < cmds->size)
		{
			pipe(fd[i]);
			t_cmd *cmd = (t_cmd *)cmds->at(cmds, i);
			dprintf(2, "INFO: Exec %s in Child\n", is_builtin(cmd->argv[0]) ? "BuiltIn" : "Cmd");
			pids[i] = run_cmd_child(cmd, fd, cmds->size, i);
		}
	}
	i = -1;
	while (++i < cmds->size)
		if (pids[i] > 0)
			wait(&pids[i]);
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

// t_cmd *create_cmd(char *arg1, char *arg2, char *arg3, char *arg4, char *arg5, int count)
// {
// 	t_cmd *cmd;

// 	cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 	cmd->argv[0] = arg1;
// 	cmd->argv[1] = arg2;
// 	cmd->argv[2] = arg3;
// 	cmd->argv[3] = arg4;
// 	cmd->argv[4] = arg5;
// 	cmd->argv[5] = NULL;
// 	cmd->count = count;
// 	cmd->redirs = new_vector();
// 	return (cmd);
// }

// t_vector *fill_commands(char *line)
// {
// 	t_vector *cmds = new_vector();

// 	t_cmd *cm1 = create_cmd(line, NULL, NULL, NULL, NULL, 1);
// 	// cm1->redirs->insert(cm1->redirs, create_redir(right, "file"));
// 	// cm1->redirs->insert(cm1->redirs, create_redir(right, "b"));
// 	// cm1->redirs->insert(cm1->redirs, create_redir(right, "c"));

// 	// t_cmd *cm2 = create_cmd("wc", "-l", NULL, NULL, NULL, 2);
// 	// cm2->redirs->insert(cm2->redirs, create_redir(left, "a"));
// 	// cm2->redirs->insert(cm2->redirs, create_redir(left, "b"));
// 	// cm2->redirs->insert(cm2->redirs, create_redir(left, "c"));
// 	// cm2->redirs->insert(cm2->redirs, create_redir(right, "e"));
// 	// cm2->redirs->insert(cm2->redirs, create_redir(right, "f"));

// 	// t_cmd *cm3 = create_cmd("cat", "f", NULL, NULL, NULL);

// 	// t_cmd *cm4 = create_cmd("BC", NULL, NULL, NULL, NULL);

// 	// t_cmd *cm5 = create_cmd("echo", "a", "+", "b", NULL);

// 	// t_cmd *cm6 = create_cmd("cat", NULL, NULL, NULL, NULL);
// 	// cm6->redirs->insert(cm6->redirs, create_redir(right, "file"));

// 	// t_cmd *cm7 = create_cmd("cat", NULL, NULL, NULL, NULL);
// 	// cm7->redirs->insert(cm7->redirs, create_redir(left, "file"));
// 	// cm7->redirs->insert(cm7->redirs, create_redir(right, "file"));

// 	///////////
// 	cmds->insert(cmds, cm1);
// 	// cmds->insert(cmds, cm2);
// 	// cmds->insert(cmds, cm3);
// 	// cmds->insert(cmds, cm4);
// 	// cmds->insert(cmds, cm5);
// 	// cmds->insert(cmds, cm6);
// 	// cmds->insert(cmds, cm7);

// 	return (cmds);
// }


