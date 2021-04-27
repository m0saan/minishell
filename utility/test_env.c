#include "ft_env.h"
#include "ft_vector.h"

char *to_string(void *item)
{
	t_var *var = (t_var *)item;
	char *str = malloc(200 * sizeof(char));
	strcat(str, "\n");
	strcat(str, "KEY: ");
	strcat(str, var->key);
	strcat(str, " ##\t\t VALUE: ");
	strcat(str, var->value != NULL ? var->value : "<NULL>");
	// char *str3 = strdup(var->value != NULL ? var->value : "none");
	return (str);
}

char *to_string2(void *item)
{
	t_var *var = (t_var *)item;

	return (var->raw);
}

int main()
{
	t_vector *env = new_vector();

	set_var(env, "var1=hakam");
	set_var(env, "var2=hakam is a good guy");
	set_var(env, "var3");
	set_var(env, "var1=google");
	// set_var(env, "var3=microsoft");
	set_var(env, "var2");

	char *key = "var4";
	printf("KEY: %s ==> VAL: %s\n", key, get_var(env, key));
	// display_vector(env, to_string);

	return (0);
}

