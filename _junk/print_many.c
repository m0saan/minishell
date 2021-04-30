#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int		print(unsigned int argc, ...)
{
	int		i;
	char	*str;
	va_list ls;

	i = -1;
	va_start(ls, argc);
	while (++i < argc)
	{
		str = va_arg(ls, char *);
		if (str != NULL)
			write(1, str, strlen(str));
		else
			write(1, "(null)", 6);
		if (i < argc - 1)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	va_end(ls);
	return (argc);
}

int main(void)
{
	char *arg = "dsjhdfshfksdfhksdjfdkjhf      jhvj      jhvjhe vhfhffeher";
	print(5, "Hello", "World", "From", NULL, arg);
	return (0);
}