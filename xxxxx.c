#include <stdio.h>

int main(int ac, char **av) {
	
	printf("AC = %d\n", ac);
	for (int i = 0; i < ac; i++) {
		printf("AV(%d) = |%s|\n", i, av[i]);
	}
	return (0);
}
