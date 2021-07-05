/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:40:56 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:33:00 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/ft_variables.h"
#include "../include/minishell.h"

static int	print_var2(t_var *var)
{
	if (var->value)
	{
		write(1, var->raw, strlen(var->raw));
		write(1, "\n", 1);
	}
	return (0);
}

int ft_env()
{
	list_vars(g_config.envp, false, print_var2);
	return (0);
}
