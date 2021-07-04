/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:15:07 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:15:35 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_variables.h"
#include "../include/ft_utility.h"
#include "../include/error.h"
#include "../include/minishell.h"

t_bool	equals_key(void *item1, void *item2)
{
	const t_var	*var1 = (t_var *)item1;
	const char	*var2_key = (char *)item2;

	return (strcmp(var1->key, var2_key) == 0);
}

t_bool	check_key(t_var *var)
{
	int		i;
	char	c;

	if (!var || !var->key)
		return (false);
	i = 0;
	c = var->key[i];
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
		return (false);
	while (var->key[++i])
	{
		c = var->key[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
				|| (c >= '0' && c <= '9') || (c == '_')))
			return (false);
	}
	return (true);
}

t_bool	check_key2(char *key)
{
	int		i;
	char	c;

	if (!key)
		return (false);
	i = 0;
	c = key[i];
	if (!(ft_isalpha(c) || (c == '_')))
		return (false);
	while (key[++i])
	{
		c = key[i];
		if (!(ft_isalnum(c) || (c == '_')))
			return (false);
	}
	return (true);
}
