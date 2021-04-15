#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

void signal_handler(int sig) {
printf("SIGNAL: %d\n", sig);
}

int main(int argc, char const *argv[])
{
	// Ctrl+\ = SIGQUIT
	// Ctrl+C = SIGINT
	// Ctrl+D = 

	pid_t pid = fork();

	if (pid == 0) {
		signal(SIGINT, signal_handler);
		execvp("cat", )

	} else {
		wait(&pid);
	}
	
	return 0;
}
