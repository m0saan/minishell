/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:13:38 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/14 12:55:15 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/error.h"
#include "../include/minishell.h"

t_var	*new_var_v(char *key, char *value, char *raw)
{
	t_var	*var;

	var = (t_var *)ft_malloc(sizeof(t_var));
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

	var = (t_var *)ft_malloc(sizeof(t_var));
	var->raw = (char *)ft_malloc((strlen(key) + strlen(value) + 2)
			* sizeof(char));
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

void	delete_var(void *var)
{
	t_var	*v;

	v = (t_var *)var;
	if (!v)
		return ;
	if (v->key)
		free(v->key);
	if (v->raw)
		free(v->raw);
	if (v->value)
		free(v->value);
	free(v);
}
