/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:20:25 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:40:01 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/error.h"
#include "../include/minishell.h"

int	predicate(void *s1, void *s2)
{
	const t_var	*ss1 = (const t_var *)s1;
	const t_var	*ss2 = (const t_var *)s2;

	return (ft_strcmp(ss1->key, ss2->key));
}

char	*get_var(t_vector *env, char *key)
{
	t_var	*var;

	var = search(env, key, equals_key);
	if (!var)
		return (NULL);
	return (var->value);
}

t_var	*get_var2(t_vector *env, char *key)
{
	t_var	*var;

	var = search(env, key, equals_key);
	return (var);
}

int	list_vars(t_vector *env, t_bool sort_, int (*print)(t_var *))
{
	t_vector	*temp_env;
	t_var		*var;
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
