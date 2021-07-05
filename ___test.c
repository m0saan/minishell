#include <stdlib.h>
#include<stdio.h>
#include "include/ft_vector.h"

static t_vector *vector;

#define new(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)

void *my_malloc(size_t size, const char *file, int line, const char *func)
{
	vector = new_vector();
	void *p = malloc(size);
	printf("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);
	insert(vector, p);
	return p;
}

int main()
{
	int *numbers = new(100);
	return 0;
}
