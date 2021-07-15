/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:16:50 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/14 21:51:28 by ehakam           ###   ########.fr       */
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

t_bool	check_value(char *val)
{
	int			i;
	int			len;
	const char	*err_msg = "numeric argument required";
	const char	*max = "9223372036854775807";
	const char	*min = "-9223372036854775808";
	char		*vals;

	i = -1;
	if (!val)
		return (false);
	vals = ft_split(val, ' ');
	if (vals[1] != NULL)
	{
		free_all(vals);
		return (p_error("exit", NULL, "numeric argument required", 1));
	}
	
	
	if (len > 19)
	while (val[++i])
		;
	return false;
}

int	ft_exit(int ac, char **av)
{
	const char		*err_msg = "too many arguments";
	unsigned char	code;

	if (!g_config.is_forked)
		write(1, "exit\n", 5);
	if (ac < 2)
		exit(0);
	code = (unsigned char)ft_atol_err(av[1]);
	if (ac > 2)
		return (p_error("exit", NULL, err_msg, 1));
	delete_free(g_config.envp, &delete_var);
	free(g_config.prompt);
	exit(code);
}
