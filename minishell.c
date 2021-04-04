#include "minishell.h"

#define IS_FIRST 0
#define IS_LAST 2
#define IS_MIDDLE 1
#define IS_FIRSTLAST 3

char *to_string(void *item)
{
	t_command *it = (t_command *)item;
	return (it->argv[0]);
}

t_command *create_command(char *arg1, char *arg2)
{
	t_command *cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->argv[0] = strdup(arg1);
	cmd->argv[1] = strdup(arg2);
	cmd->argv[2] = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

t_vector *fill_commands()
{
	t_vector *v = new_vector();

	t_command *cmd = create_command("ls", "-la");
	t_command *cmd2 = create_command("grep", "drw");
	t_command *cmd3 = create_command("cat", "-e");
	t_command *cmd4 = create_command("grep", "Jan");

	insert(v, cmd);
	insert(v, cmd2);
	insert(v, cmd3);
	insert(v, cmd4);

	return (v);
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

void setup_pipes(int fd[][2], int position, int index)
{
	const int prev_idx = index - 1;

	if (position == IS_FIRST)
	{
		dprintf(2, "CHILD: DUP(1) INDEX(%d)\n", index);
		dup2(fd[index][1], 1);
		close(fd[index][0]);
	}
	else if (position == IS_MIDDLE)
	{
		dprintf(2, "CHILD: DUP(ALL) INDEX(%d, %d)\n", prev_idx, index);
		dup2(fd[prev_idx][0], 0);
		dup2(fd[index][1], 1);
		close(fd[prev_idx][1]);
	}
	else if (position == IS_LAST)
	{
		dprintf(2, "CHILD: DUP(0) INDEX(%d)\n", prev_idx);
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

pid_t run_command(t_command *cmd, int fd[][2], t_size size, int index)
{
	pid_t pid;
	int pos;

	if ((pid = fork()) < 0)
		ft_exit("Error\nFORK FAILED!", -1);
	pos = get_position(size, index);
	if (pid == 0)
	{
		setup_pipes(fd, pos, index);
		dprintf(2, "CHILD: EXEC(%s)\n", cmd->argv[0]);
		execvp(cmd->argv[0], cmd->argv);
		ft_exit("Error\nEXECVE FAILED!", -1);
	}
	if (pos == IS_FIRST)
		close(fd[index][1]);
	if (pos == IS_MIDDLE)
	{
		close(fd[index - 1][0]);
		close(fd[index][1]);
	}
	if (pos == IS_LAST)
		close(fd[index - 1][0]);
	return pid;
}

int main(int ac, char **av, char **env)
{
	int i = -1;
	int j = -1;
	int fd[100][2];
	pid_t pids[64];
	t_pair *pair;

	t_vector *cmds = fill_commands();

	while (++i < cmds->size)
	{
		pipe(fd[i]);
		printf("PARENT:LOOP INDX: %d\n", i);
		t_command *cmd = (t_command *)at(cmds, i);
		pids[i] = run_command(cmd, fd, cmds->size, i);
	}
	// i = -1;
	// while (++i < cmds->size)
	// {
	// 	close(fd[i][0]);
	// 	close(fd[i][1]);
	// }
	i = -1;
	while (++i < cmds->size)
		if (pids[i] > 0)
			wait(&pids[i]);

	return (0);
}