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

	t_command *cmd = create_command("ls", "-l");
	t_command *cmd2 = create_command("grep", "drw");
	// t_command *cmd3 = create_command("echo", "hakam 3");

	insert(v, cmd);
	insert(v, cmd2);
	// insert(v, cmd3);

	return (v);
}

int get_position(t_size size, t_size index)
{
	if (size == 1)
		return (IS_FIRSTLAST);
	if (index == 0)
		return (IS_FIRST);
	if (index == size - 1)
		return (IS_LAST);
	return (IS_MIDDLE);
}

void setup_pipes(int fd[2], t_size position)
{
	dprintf(2, "CHILD: DUPPING...POS(%lu)\n", position);
	if (position == IS_MIDDLE)
	{
		dprintf(2, "CHILD: DUP(ALL)\n");
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	}
	else if (position == IS_FIRST)
	{
		dprintf(2, "CHILD: DUP(1)\n");
		dup2(fd[1], 1);
	}
	else if (position == IS_LAST)
	{
		dprintf(2, "CHILD: DUP(0)\n");
		dup2(fd[0], 0);
	}
	else
		dprintf(2, "CHILD: DUP(NONE)\n");
	close(fd[0]);
	close(fd[1]);
}

pid_t run_command(t_command *cmd, int fd[2], t_size size, t_size index)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		ft_exit("Error\nFORK FAILED!", -1);
	if (pid == 0)
	{
		setup_pipes(fd, get_position(size, index));
		dprintf(2, "CHILD: EXEC(%s)\n", cmd->argv[0]);
		execvp(cmd->argv[0], cmd->argv);
		ft_exit("Error\nEXECVE FAILED!", -1);
	}
	return pid;
}

int main(int ac, char **av, char **env)
{
	int i = -1;
	int j = -1;
	int fd[2];
	pid_t pids[64];

	t_vector *cmds = fill_commands();
	display_vector(cmds, to_string);

	pipe(fd);
	// while (++i < cmds->size)
	// {
	// 	printf("PARENT:LOOP INDX: %d\n", i);
	// 	t_command *cmd = (t_command *)at(cmds, i);
	// 	run_command(cmd, fd, cmds->size, i);
	// }
	t_command *cmd1 = (t_command *)at(cmds, 0);
	pid_t p1 = run_command(cmd1, fd, cmds->size, 0);
	t_command *cmd2 = (t_command *)at(cmds, 1);
	pid_t p2 = run_command(cmd2, fd, cmds->size, 1);

	if (p1 != 0)
		waitpid(p1, NULL, 0);
	if (p2 != 0)
		waitpid(p2, NULL, 0);

	close(fd[0]);
	close(fd[1]);

	return (0);
}