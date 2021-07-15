/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:16:50 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/15 11:39:36 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/error.h"
#include "../include/ft_types.h"
#include "../include/minishell.h"

void	free_all(char **all)
{
	int		i;

	if (!all)
		return ;
	i = -1;
	while (all[++i])
		free(all[i]);
	free(all);
}

t_bool	ft_isdigits(char *val)
{
	int		i;

	i = 0;
	if (!val || !val[0])
		return (false);
	if (val[i] == '-')
		i++;
	while (val[i])
		if (!ft_isdigit(val[i++]))
			return (false);
	return (true);
}

t_bool	check_value(char *val)
{
	t_bool		code;
	char		**vals;

	code = true;
	if (!val || !val[0])
		return (false);
	vals = ft_split(val, ' ');
	if (vals[1] != NULL || !ft_isdigits(vals[0]))
		code = p_error("exit", val, "numeric argument required", false);
	else if (vals[0][0] != '-' && ft_strlen(vals[0]) == 19)
	{
		if (ft_strcmp(vals[0], MAXVAL) > 0)
			code = p_error("exit", val, "numeric argument required", false);
	}
	else if (vals[0][0] == '-' && ft_strlen(vals[0]) == 20)
	{
		if (ft_strcmp(vals[0], MINVAL) > 0)
			code = p_error("exit", val, "numeric argument required", false);
	}
	else if ((vals[0][0] != '-' && ft_strlen(vals[0]) > 19)
		|| (vals[0][0] == '-' && ft_strlen(vals[0]) > 20))
		code = p_error("exit", val, "numeric argument required", false);
	free_all(vals);
	return (code);
}

int	ft_exit(int ac, char **av)
{
	unsigned char	code;

	if (!g_config.is_forked)
		write(1, "exit\n", 5);
	if (ac < 2)
		exit(0);
	if (!check_value(av[1]))
		exit(255);
	code = (unsigned char)ft_atol(av[1]);
	if (ac > 2)
		return (p_error("exit", NULL, "too many arguments", 1));
	delete_free(g_config.envp, &delete_var);
	free(g_config.prompt);
	exit(code);
}
