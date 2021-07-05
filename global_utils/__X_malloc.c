//
// Created by Mohammad  Boustta on 7/5/21.
//

#include "../include/global_utils.h"
#include "../include/minishell.h"


void *my_malloc(size_t size, const char *file, int line, const char *func)
{
	void *p = malloc(size);
	printf("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);
	insert(g_config.x_malloc_vec, p);
	return p;
}