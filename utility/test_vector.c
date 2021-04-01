#include "ft_vector.h"

void print(void *item) {
	int *it = (int *)item;
	printf("%d", *it);
}

int main() {


	t_vector *v = new_vector_s(4);

	int xx = 10;
	insert(v, &xx);
	int bb = 234;
	insert(v, &bb);
	int cc = 86;
	insert(v, &cc);
	int dd = 31;
	insert(v, &dd);

	t_vector *v2 = new_vector_s(10);

	copy(v, v2);

	display_vector(v, print);
	delete(&v);
	return (0);
}