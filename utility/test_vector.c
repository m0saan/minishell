#include "ft_vector.h"

int stringlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void scopy(char *src, char *dest)
{
	if (!src || !dest)
		return;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char *new_string(size_t len)
{
	return (char *)malloc(len * sizeof(char));
}

char *join_char(char *s, char c, t_bool fre)
{
	char *newstr;
	int slen = 0;
	if (!s)
	{
		newstr = new_string(2);
		newstr[0] = c;
		newstr[1] = '\0';
		return newstr;
	}
	slen = stringlen(s);
	newstr = new_string(slen + 2);
	scopy(s, newstr);
	newstr[slen] = c;
	newstr[slen + 1] = '\0';
	if (fre)
		free(s);
	return (newstr);
}

void numbr_tostr(char **snum, long num)
{
	if (num < 0)
	{
		num = -num;
		*snum = join_char(*snum, '-', false);
	}
	if (num >= 0 && num <= 9)
		*snum = join_char(*snum, num + 48, false);
	if (num > 9)
	{
		numbr_tostr(snum, num / 10);
		numbr_tostr(snum, num % 10);
	}
}

char *to_string(void *item)
{
	int *it = (int *)item;
	char *num = NULL;
	numbr_tostr(&num, *it);
	return (num);
}

int *copy_int(int value)
{
	int *new_value = malloc(sizeof(int));
	*new_value = value;
	return (new_value);
}

int main()
{
	t_vector v = new_vector_s(15);
	int i = 0;

	while (i < 11)
	{
		int *xx = copy_int(i);
		insert(&v, xx);
		i += 1;
	}

	int *zz = v.data[11];

	move_to_last(&v, 0);
	move_to_last(&v, 6);
	//move_to_last(&v, 0);
	
	// printf("value: %d\n", *(int *)at(&v, 0));
	// t_vector v2 = new_vector_from(&v);
	// int *xx = copy_int(55);
	// insert(&v2, xx);
	display_vector(&v, to_string);
	// display_vector(&v2, to_string);
	delete (&v);
	return (0);
}