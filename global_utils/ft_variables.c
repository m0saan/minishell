/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:13:38 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:20:37 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/ft_utility.h"
#include "../include/error.h"
#include "../include/minishell.h"

// int		predicate(void *s1, void *s2)
// {
// 	const t_var	*ss1 = (const t_var *)s1;
// 	const t_var	*ss2 = (const t_var *)s2;
//
// 	return (ft_strcmp(ss1->key, ss2->key));
// }

t_var	*new_var_v(char *key, char *value, char *raw)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->key = key;
	var->value = value;
	var->raw = raw;
	return (var);
}

t_var	*new_var_kv(char *key, char *value)
{
	int		i;
	int		j;
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var->raw = (char *)malloc((strlen(key) + strlen(value) + 2) * sizeof(char));
	bzero(var->raw, (strlen(key) + strlen(value) + 2));
	var->key = key;
	var->value = value;
	i = -1;
	j = 0;
	while (key[++i])
		var->raw[j++] = key[i];
	var->raw[j++] = '=';
	i = -1;
	while (value[++i])
		var->raw[j++] = value[i];
	var->raw[j] = '\0';
	return (var);
}

t_var	*new_var_s(char *var_str)
{
	int		index_of_eq;
	char	*value;

	index_of_eq = index_of_c(var_str, '=');
	if (index_of_eq == -1)
		return (new_var_v(strdup(var_str), NULL, strdup(var_str)));
	value = ft_substr(var_str, index_of_eq + 1, strlen(var_str));
	if (!value)
		value = strdup("");
	return (new_var_v(ft_substr(var_str, 0, index_of_eq), value,
			strdup(var_str)));
}

int		list_vars(t_vector *env, t_bool sort_, int (*print)(t_var *))
{
	t_vector	*temp_env;
	t_var		*var;
	char		*var_name;
	char		*var_value;
	int			i;

	i = -1;
	temp_env = new_vector_from(env);
	if (sort_)
		sort(temp_env, predicate);
	while (++i < (int)temp_env->size)
	{
		var = (t_var *)at(env, i);
		if (ft_strcmp(var->key, "?") != 0)
			print(var);
	}
	delete(temp_env);
	return (0);
}

void	delete_var(t_var *var)
{
	if (!var)
		return ;
	if (var->key)
		free(var->key);
	if (var->raw)
		free(var->raw);
	if (var->value)
		free(var->value);
	free(var);
}




