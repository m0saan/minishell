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

int  predicate(void *s1, void *s2)
{
	const t_var *ss1 = (const t_var *)s1;
	const t_var *ss2 = (const t_var *)s2;
	return (strcmp(ss1->key, ss2->key));
}

int main()
{
	t_vector *env = new_vector();

	set_var(env, "_var1=hakam");
	set_var(env, "var2=hakam is a good guy");
	set_var(env, "lvar3");
	set_var(env, "Zvar1=");
	set_var(env, "Fvar3=microsoft");
	set_var(env, "aaaavar2");
	// t_bool valid = check_key(split_key_value_v("var5=hakam"));
	// printf("VALID: %s\n", valid == 0 ? "FALSE" : "TRUE");
	// char *key = "var4";
	// printf("KEY: %s ==> VAL: %s\n", key, get_var(env, key));
	env->sort(env, predicate);
	display_vector(env, to_string);

	return (0);
}

