/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:13:38 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/25 17:52:18 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "ft_env.h"

static char *ft_substr(char *str, int from, int to)
{
	int		i;
	int		len;
	char	*sub;
	
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

static int index_of(char *str, char c)
{
	int		i;
	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

t_var	*new_var()
{
	t_var *var;
	
	var = (t_var *)malloc(sizeof(t_var));
	return (var);
}

t_var	*new_var_v(char *key, char *value, char *raw)
{
	t_var *var;
	var = (t_var *)malloc(sizeof(t_var));
	var->key = key;
	var->value = value;
	var->raw = raw;
	return (var);
}

t_var	*split_key_value(struct s_var *var, char *var_str)
{
	int		index_of_eq;

	if ((index_of_eq = index_of(var_str, '=')) == -1)
	{
		var->key = strdup(var_str);
		var->value = NULL;
		var->raw = strdup(var_str);
		return (var);
	}
	var->key = ft_substr(var_str, 0, index_of_eq);
	var->value = ft_substr(var_str, index_of_eq + 1, strlen(var_str));
	var->raw = strdup(var_str);
	return (var);
}

t_var	*split_key_value_v(char *var_str)
{
	int		index_of_eq;
	if ((index_of_eq = index_of(var_str, '=')) == -1)
		return (new_var_v(strdup(var_str), NULL, var_str));
	return (new_var_v(ft_substr(var_str, 0, index_of_eq),
			ft_substr(var_str, index_of_eq + 1, strlen(var_str)),
			var_str));
}

t_bool	equals(void *item1, void *item2)
{
	t_var *var1 = (t_var *)item1;
	t_var *var2 = (t_var *)item2;
	return (strcmp(var1->key, var2->key) == 0);
}

t_bool	equals_key(void *item1, void *item2)
{
	t_var *var1 = (t_var *)item1;
	char *var2_key = (t_var *)item2;
	return (strcmp(var1->key, var2_key) == 0);
}

int		set_var(t_vector *env, char *var_str)
{
	t_var	*var;
	t_var	*existing_var;

	var = split_key_value_v(var_str);
	existing_var = env->search(env, var->key, equals_key);
	if (!existing_var)
		env->insert(env, var);
	else if (var->value)
	{
		free(existing_var->value);
		free(existing_var->key);
		free(existing_var->raw);
		existing_var->value = var->value;
		existing_var->key = var->key;
		existing_var->raw = var->raw;
		free(var);
	}
	else
	{
		free(var->key);
		free(var->raw);
		free(var);
	}
	return (0);
}

char	*get_var(t_vector *env, char *key)
{
	t_var	*var;

	var = env->search(env, key, equals_key);
	if (!var)
		return (NULL);
	return (var->value);
}

t_var	*get_var_2(t_vector *env, char *key)
{
	t_var	*var;

	var = env->search(env, key, equals_key);
	return (var);
}

// int main(void)
// {
// 	char *str = "ha==kam";
	
// 	t_var *var = split_key_value_v(str);
	
// 	printf("RAW: |%s|\nKEY: |%s| VALUE: |%s|\n",str, var->key, var->value);
// 	return (0);
// }