#include "ft_vector.h"
#include "../minishell.h"

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
	t_command *it = (t_command *)item;
	return (it->argv[1]);
}

int *copy_int(int value)
{
	int *new_value = malloc(sizeof(int));
	*new_value = value;
	return (new_value);
}

t_command create_command(char *arg1, char *arg2)
{
	// t_command *cmd;

	// cmd = (t_command *)malloc(sizeof(t_command));
	// cmd->argv[0] = strdup(arg1);
	// cmd->argv[1] = strdup(arg2);
	// cmd->redirs = NULL;

	t_command cmd;

	//cmd = (t_command *)malloc(sizeof(t_command));
	cmd.argv[0] = strdup(arg1);
	cmd.argv[1] = strdup(arg2);
	cmd.redirs = NULL;
	return (cmd);
}

t_vector *create_vector() {
	t_vector *v = new_vector_s(10);
	int i = 0;

	t_command cmd = create_command("ls", "-la");
	insert(v, &cmd);
	t_command cmd2 = create_command("grep", "-i");
	insert(v, &cmd2);
	t_command cmd3 = create_command("cat", "-e");
	insert(v, &cmd3);
	return (v);
}

void ddd(int fd[2]) {
	fd[0] = 1;
	fd[1] = 2;
}

int main()
{
	// t_vector *v = create_vector();
	// display_vector(v, to_string);

	int fd[2];

	fd[0] = 100;
	fd[1] = 200;

	printf("===0: %d ===\n", fd[0]);
	printf("===1: %d ===\n", fd[1]);
	ddd(fd);

	printf("===0: %d ===\n", fd[0]);
	printf("===1: %d ===\n", fd[1]);

	return (0);
}