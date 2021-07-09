/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:15:10 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:38:40 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/error.h"
#include "../include/minishell.h"

int	update_var(t_var *existing_var, t_var *new_var)
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

int	set_var(t_vector *env, char *var_str)
{
	t_var	*var;
	t_var	*existing_var;

	var = new_var_s(var_str);
	if (!check_key(var))
	{
		free(var->key);
		free(var->raw);
		if (var->value)
			free(var->value);
		return (p_error("export", var_str, "not a valid identifier", 1));
	}
	existing_var = search(env, var->key, equals_key);
	if (!existing_var)
		insert(env, var);
	else if (var->value)
		update_var(existing_var, var);
	else
	{
		free(var->key);
		free(var->raw);
		free(var);
	}
	return (0);
}

int	set_var2(t_vector *env, char *key, char *value, t_bool check)
{
	t_var	*var;
	t_var	*existing_var;

	var = new_var_kv(strdup(key), strdup(value));
	if (check && !check_key(var))
	{
		delete_var(var);
		return (p_error("export", key, "not a valid identifier", 1));
	}
	existing_var = search(env, var->key, equals_key);
	if (!existing_var)
		insert(env, var);
	else if (var->value)
		update_var(existing_var, var);
	else
		delete_var(var);
	return (0);
}

int	unset_var(t_vector *env, char *key)
{
	int		index;
	t_var	*deleted_var;

	if (!key)
		return (1);
	if (!check_key2(key))
		return (p_error("unset", key, "not a valid identifier", 1));
	index = index_of(env, key, equals_key);
	if (index == -1)
		return (0);
	deleted_var = (t_var *)remove_at(env, index);
	delete_var(deleted_var);
	return (0);
}
