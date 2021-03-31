/*
In this example, two children processes are created.
The first one executes the command "ls -l". Its output
is redirected to a pipe. The second one executes
"grep pipe". Its input is redirected from the
pipe the first process' output is written to. So,
the overall command lists all the *pipe* files.
The father process waits for the children to finish,
before continuing execution. This is an example of
how the "|" operator should work.

Compilation: gcc pipe-redirection.c -o pipe-redirection -Wall
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	int fd[2];
	pid_t pid1, pid2;
	char *argv[5];

	pipe(fd);

	/* Create the first child and run the first command. */
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("First fork() failed!");
		return -1;
	}
	if (pid1 == 0)
	{
		/* Set the process output to the input of the pipe. */
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		argv[0] = (char *)malloc(5 * sizeof(char));
		argv[1] = (char *)malloc(5 * sizeof(char));
		strcpy(argv[0], "ls");
		strcpy(argv[1], "-l");
		argv[2] = NULL;
		fprintf(stderr, "************* Running ls -l *************\n");
		execvp(argv[0], argv);
		perror("First execvp() failed");
		return -1;
	}

	/* Create the second child and run the second command. */
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Second fork() failed!");
		return -1;
	}
	if (pid2 == 0)
	{
		/* Set the process input to the output of the pipe. */
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		argv[0] = (char *)malloc(5 * sizeof(char));
		argv[1] = (char *)malloc(5 * sizeof(char));
		strcpy(argv[0], "grep");
		strcpy(argv[1], "cd");
		argv[2] = NULL;
		fprintf(stderr, "************* Running grep pipe *************\n");
		execvp(argv[0], argv);
		perror("Second execvp() failed");
		return -1;
	}

	close(fd[0]);
	close(fd[1]);
	/* Wait for the children to finish, then exit. */
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("************* Father exitting... *************\n");
	return 0;
}