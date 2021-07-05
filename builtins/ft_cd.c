/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:40:36 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:40:38 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/ft_variables.h"
#include "../include/minishell.h"

int	ft_cd(int ac, char **av)
{
	int		ret;
	char	pwd[1025];

	ret = 0;
	if (ac == 1)
		ret = chdir(get_var(g_config.envp, "HOME"));
	else if (ac >= 2)
		ret = chdir(av[1]);
	if (ret == -1)
		return (p_error("cd", av[1], NULL, 1));
	set_var2(g_config.envp, "OLDPWD", get_var(g_config.envp, "PWD"), true);
	getcwd(pwd, 1024);
	set_var2(g_config.envp, "PWD", pwd, true);
//	if (g_config.prompt)
//		free(g_config.prompt);
	//g_config.prompt = strjoin_s(pwd, " _$ ", false);
	return (0);
}
