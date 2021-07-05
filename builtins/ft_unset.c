/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:41:25 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:41:27 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/ft_variables.h"
#include "../include/minishell.h"

int	ft_unset(int ac, char **av)
{
	int		i;
	int		code;

	if (ac == 1)
		return (0);
	i = 0;
	code = 0;
	while (av[++i])
		if (unset_var(g_config.envp, av[i]) != 0)
			code = 1;
	return (code);
}
