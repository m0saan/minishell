#include "minishell.h"

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
	t_command *cmd2 = create_command("cat", "-e");
	t_command *cmd3 = create_command("echo", "hakam");

	insert(v, cmd);
	insert(v, cmd3);
	insert(v, cmd2);

	return (v);
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
	while (++i < cmds->size)
	{
		printf("PARENT:LOOP INDX: %d\n", i);
		pid_t pid = fork();
		printf("FORK: PID: %d\n", pid);
		if (pid < 0)
			ft_exit("Error\nFork Failed!", 1);
		if (pid != 0)
		{
			printf("===>: PID: %d\n", pid);
			pids[i] = pid;
		}
		if (pid == 0)
		{
			// printf("CHILD: PID: %d\n", pid);
			t_command *cmd = (t_command *)at(cmds, i);
			if (i == 0 && cmds->size > 1)
			{
				dup2(fd[1], 1);
				printf("CHILD: DUP (1): INDEX %d\n", i);
			}
			if (i == cmds->size - 1 && cmds->size > 1)
			{
				dup2(fd[0], 0);
				printf("CHILD: DUP (0): INDEX %d\n", i);
			}
			if (i > 0 && i < cmds->size - 1)
			{
				dup2(fd[1], 1);
				dup2(fd[0], 0);
				printf("CHILD: DUP (0, 1): INDEX %d\n", i);
			}
			else
				printf("CHILD: DUP (NONE): INDEX %d\n", i);
			close(fd[0]);
			close(fd[1]);
			printf("CHILD: EXECV(%s)\n", cmd->argv[0]);
			execvp(cmd->argv[0], cmd->argv);
			printf("CHILD: EXECV FAILED\n");
			exit(0);
		}
	}
	i = -1;
	while (++i < cmds->size)
	{
		printf("<===:%d\n", pids[i]);
		waitpid(pids[i], NULL, 0);
	}
	
	close(fd[0]);
	close(fd[1]);

	return (0);
}