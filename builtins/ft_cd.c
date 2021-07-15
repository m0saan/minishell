/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:40:36 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/15 17:46:25 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/ft_variables.h"
#include "../include/minishell.h"

int	cd_oldpwd(void)
{
	int		ret;
	char	*path;
	char	pwd[1025];

	ret = 0;
	path = get_var(g_config.envp, "OLDPWD");
	if (!path)
		return (p_error("cd", NULL, "OLDPWD not set", 1));
	if (!path[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	else
		ret = chdir(path);
	if (ret == -1)
		return (p_error("cd", path, NULL, 1));
	getcwd(pwd, 1024);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int	ft_cd(int ac, char **av)
{
	int		ret;
	char	pwd[1025];

	ret = 0;
	if (ac == 1)
		ret = chdir(get_var(g_config.envp, "HOME"));
	if (ac >= 2 && ft_strcmp(av[1], "-") == 0)
	{
		if (cd_oldpwd() == 1)
			return (1);
	}
	else if (ac >= 2)
		ret = chdir(av[1]);
	if (ret == -1)
		return (p_error("cd", av[1], NULL, 1));
	set_var2(g_config.envp, "OLDPWD", get_var(g_config.envp, "PWD"), false);
	getcwd(pwd, 1024);
	set_var2(g_config.envp, "PWD", pwd, false);
	if (g_config.prompt)
		free(g_config.prompt);
	g_config.prompt = strjoin_s(pwd, " _$ ", false);
	return (0);
}
