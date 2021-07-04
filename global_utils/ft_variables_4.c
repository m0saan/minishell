/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:20:25 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:20:43 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/ft_utility.h"
#include "../include/error.h"
#include "../include/minishell.h"

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
