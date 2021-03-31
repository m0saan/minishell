#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	pid_t child;

	pipe(fd);

	if ((child = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}

	if (child == 0)
	{
		/* Child process closes up input side of pipe */
		printf("This is child\n %d\n " , child);
		close(fd[0]);
	}
	else
	{
		/* Parent process closes up output side of pipe */
		printf("This is parent\n %d\n", child);
		close(fd[1]);
	}
	return (0);
}