#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

pid_t current_child_pid;

void signal_handler(int sig) {
	printf("^\\\n");
	// kill(current_child_pid, SIGQUIT);
}

void run()
{
	pid_t pid = fork();

	if (pid == 0) {
		signal(SIGQUIT, signal_handler);
		char *argv2[10];
		argv2[0] = "cat";
		argv2[1] = NULL;
		execvp(argv2[0], argv2);
		dprintf(2, "Error\n");
		exit(1);
	} else {
		current_child_pid = pid;
		signal(SIGQUIT, signal_handler);
		wait(&pid);
	}
}

int main(int argc, char const *argv[])
{
	// Ctrl+\ = SIGQUIT
	// Ctrl+C = SIGINT
	// Ctrl+D = 
	int x;

	while (1)
	{
		printf(">> ");
		scanf("%d", &x);
		if (x == 0)
			exit(0);
		else if (x == 1)
			run();
		else
			continue;
	}

	// char buff[1024];
	// int ret;

	// while (1)
	// {
	// 	ret = read(0, buff, 512);
	// 	if (ret <= 0)
	// 		break;
	// 	buff[ret] = '\0';
	// 	printf("OUT: %s", buff);
	// 	if (strncmp(buff, "CD", 2) == 0) {
	// 		printf("CLOSING FD 0\n");
	// 		close(0);
	// 	}
	// }

	// printf("EXIT %d\n", ret);
	// if (ret < 0) {
	// 	printf("ERROR\n");
	// }

	return 0;
}



