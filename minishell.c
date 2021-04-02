#include "minishell.h"

t_command *fill_commands()
{
	t_command *cmds = malloc(sizeof(t_command) * 5);

	t_command cmd;
	
	cmd.argv[0] = strdup("ls");
	cmd.argv[1] = strdup("-la");
	cmd.argv[2] = NULL;
	// t_vector redirs = new_vector();
	// t_redir red;
	// red.type = right;
	// red.arg = "newfile";
	// insert(&redirs, &red);
	// cmd.redirs = redirs;

	cmds[0] = cmd;
	
	cmd = cmds[0];

	int i = 0;
	while (cmd.argv[i] != NULL)
	{
		printf("=========== |%s|\n", cmd.argv[i++]);
	}
	// t_command cmd2;
	// cmd2.argv[0] = "cat";
	// cmd2.argv[1] = NULL;
	// insert(&cmds, &cmd2);

	// t_command cmd3;
	// cmd3.argv[0] = "cat";
	// cmd3.argv[1] = NULL;
	// insert(&cmds, &cmd3);

	return (cmds);
}

int main(int ac, char **av, char **env)
{
	int i = -1;
	int j = -1;
	int fd[2];
	pid_t pids[64];

	t_command *cmds = fill_commands();
	pipe(fd);
	while (++i < 1)
	{
		printf("PARENT:loop num: %d\n", i);
		pid_t pid = 0;//fork();
		printf("FORK: PID: %d\n", pid);
		if (pid < 0)
			ft_exit("Error\nFork Failed!", 1);
		if (pid != 0) {
			printf("PARENT: WAITING PID: %d\n", pids[j]);
			waitpid(pid, NULL, 0);
		}
		if (pid == 0)
		{
			printf("CHILD: PID: %d\n", pid);
			t_command cmd = cmds[0];
			printf("CHILD: EXECV(%s)\n", cmd.argv[0]);
			if (i == 0 && i != 1 - 1) {
				dup2(fd[1], 1);
				printf("CHILD: DUP (1): INDEX %d\n", i);
			}
			else if (i == 1 - 1 && i != 0) {
				dup2(fd[0], 0);
				printf("CHILD: DUP (0): INDEX %d\n", i);
			}
			else if (i > 0 && i < 1 - 1)
			{
				dup2(fd[1], 1);
				dup2(fd[0], 0);
				printf("CHILD: DUP (0, 1): INDEX %d\n", i);
			} else
				printf("CHILD: DUP (NONE): INDEX %d\n", i);
				close(fd[0]);
				close(fd[1]);
			
			//printf("CHILD: EXECV(%s)\n", cmd.argv[0]);
			//execvp(cmd.argv[0], cmd.argv);
			printf("CHILD: EXECV FAILED\n");
		} else {
			// printf("PARENT: STORING PID: %d\n", pid);
			// pids[i] = pid;
		}
	}
	// while (++j <= i)
	// {
	// 	printf("PARENT: WAITING PID: %d\n", pids[j]);
	// 	waitpid(pids[j], NULL, 0);
	// }

	close(fd[0]);
	close(fd[1]);

	return (0);
}