/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:13:38 by ehakam            #+#    #+#             */
/*   Updated: 2021/05/25 18:38:17 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

char **extract_envp(t_vector *g_env)
{
	char	**envp;
	t_var	*var;
	int		i;
	int		j;

	i = -1;
	j = 0;
	envp = (char **)malloc((g_env->size + 1) * sizeof(char *));
	while (++i < g_env->size)
	{
		var = (t_var *)g_env->at(g_env, i);
		if (var->value != NULL)
			envp[j++] = var->raw;
	}
	envp[j] = NULL;
	return (envp);
}

int predicate(void *s1, void *s2)
{
	const t_var *ss1 = (const t_var *)s1;
	const t_var *ss2 = (const t_var *)s2;
	return (strcmp(ss1->key, ss2->key));
}

char *ft_substr2(char *str, int from, int to)
{
	int i;
	int len;
	char *sub;

	i = 0;
	if (!str)
		return (NULL);
	len = strlen(str);
	if (from < 0 || from >= to || from >= len || to > len)
		return (NULL);
	sub = (char *)malloc((to - from + 1) * sizeof(char));
	while (from < to)
		sub[i++] = str[from++];
	sub[i] = '\0';
	return (sub);
}

int index_of_c(char *str, char c)
{
	int i;
	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

t_var *new_var()
{
	t_var *var;

	var = (t_var *)malloc(sizeof(t_var));
	return (var);
}

t_var *new_var_v(char *key, char *value, char *raw)
{
	t_var *var;
	var = (t_var *)malloc(sizeof(t_var));
	var->key = key;
	var->value = value;
	var->raw = raw;
	return (var);
}

t_var *new_var_kv(char *key, char *value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->raw = (char *)malloc((strlen(key) + strlen(value) + 2) * sizeof(char));
	var->key = key;
	var->value = value;
	strcat(var->raw, key);
	strcat(var->raw, "=");
	strcat(var->raw, value);
	return (var);
}

t_var *split_key_value(struct s_var *var, char *var_str)
{
	int index_of_eq;

	if ((index_of_eq = index_of_c(var_str, '=')) == -1)
	{
		var->key = strdup(var_str);
		var->value = NULL;
		var->raw = strdup(var_str);
		return (var);
	}
	var->key = ft_substr2(var_str, 0, index_of_eq);
	var->value = ft_substr2(var_str, index_of_eq + 1, strlen(var_str));
	if (!var->value)
		var->value = strdup("");
	var->raw = strdup(var_str);
	return (var);
}

t_var *split_key_value_v(char *var_str)
{
	int index_of_eq;
	char *value;

	if ((index_of_eq = index_of_c(var_str, '=')) == -1)
		return (new_var_v(strdup(var_str), NULL, strdup(var_str)));
	value = ft_substr2(var_str, index_of_eq + 1, strlen(var_str));
	if (!value)
		value = strdup("");
	return (new_var_v(ft_substr2(var_str, 0, index_of_eq), value,
					  strdup(var_str)));
}

t_bool equals(void *item1, void *item2)
{
	t_var *var1 = (t_var *)item1;
	t_var *var2 = (t_var *)item2;
	return (strcmp(var1->key, var2->key) == 0);
}

t_bool equals_key(void *item1, void *item2)
{
	t_var *var1 = (t_var *)item1;
	char *var2_key = (char *)item2;
	return (strcmp(var1->key, var2_key) == 0);
}

t_bool check_key(t_var *var)
{
	int i;
	char c;

	if (!var)
		return (false);
	i = 0;
	c = var->key[i];
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
		return (false);
	while (var->key[++i])
	{
		c = var->key[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_')))
			return (false);
	}
	return (true);
}

t_bool check_key2(char *key)
{
	int i;
	char c;

	if (!key)
		return (false);
	i = 0;
	c = key[i];
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
		return (false);
	while (key[++i])
	{
		c = key[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_')))
			return (false);
	}
	return (true);
}

int update_var(t_vector *env, t_var *existing_var, t_var *new_var)
{
	if (existing_var->value != NULL)
		free(existing_var->value);
	free(existing_var->key);
	free(existing_var->raw);
	existing_var->value = new_var->value;
	existing_var->key = new_var->key;
	existing_var->raw = new_var->raw;
	free(new_var);
	return (0);
}

int set_var(t_vector *env, char *var_str)
{
	t_var *var;
	t_var *existing_var;

	var = split_key_value_v(var_str);
	if (!check_key(var))
	{
		// Replace with EXIT
		write(2, "Error: Key Name is not Valid!", 30);
		free(var->key);
		free(var->raw);
		if (var->value)
			free(var->value);
		return (1);
	}
	existing_var = env->search(env, var->key, equals_key);
	if (!existing_var)
		env->insert(env, var);
	else if (var->value) 
		update_var(env, existing_var, var);
	else
	{
		free(var->key);
		free(var->raw);
		free(var);
	}
	return (0);
}

int set_var2(t_vector *env, char *key, char *value)
{
	t_var *var;
	t_var *existing_var;

	var = new_var_kv(key, value);
	if (!check_key(var))
	{
		// Replace with EXIT
		write(2, "Error: Key Name is not Valid!", 30);
		free(var->key);
		free(var->raw);
		if (var->value)
			free(var->value);
		return (1);
	}
	existing_var = env->search(env, var->key, equals_key);
	if (!existing_var)
		env->insert(env, var);
	else if (var->value) 
		update_var(env, existing_var, var);
	else
	{
		free(var->key);
		free(var->raw);
		free(var);
	}
	return (0);
}

int unset_var(t_vector *env, char *key)
{
	int		index;
	t_var	*deleted_var;

	if (!key)
		return (1);
	if (!check_key2(key))
	{
		write(1, "ERROR\n", 6);
		return (1);
	}
	index = env->index_of(env, key, equals_key);
	if (index == -1)
		return (0);
	deleted_var = (t_var *)env->remove_at(env, index);
	free(deleted_var->key);
	free(deleted_var->raw);
	if (deleted_var->value)
		free(deleted_var->value);
	free(deleted_var);
	return (0);
}

char *get_var(t_vector *env, char *key)
{
	t_var *var;

	var = env->search(env, key, equals_key);
	if (!var)
		return (NULL);

	return (var->value);
}

t_var *get_var_2(t_vector *env, char *key)
{
	t_var *var;

	var = env->search(env, key, equals_key);
	if (!var)
		return (NULL);

	return (var);
}

int list_vars(t_vector *env, t_bool sort_, int(*print)(t_var*))
{
	t_vector *temp_env;
	t_var	*var;
	char *var_name;
	char *var_value;
	int  i;

	i = -1;
	temp_env = new_vector_from(env);
	if (sort_)
		sort(temp_env, predicate);
	while (++i < temp_env->size)
	{
		var = (t_var *)temp_env->at(env, i);
		if (strcmp(var->key, "?") != 0)
			print(var);
	}
	delete(temp_env);
	return (0);
}

