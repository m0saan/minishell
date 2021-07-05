/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:14:12 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:06:41 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool		is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "cd") == 0);
}

int			ft_exec_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env());
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->count, cmd->argv));
	return (0);
}

int			ft_find_and_exec(t_cmd *cmd, char **envp)
{
	t_vector	*paths;
	int			i;

	i = -1;
	paths = get_paths(get_var(g_config.envp, "PATH"), cmd->argv[0]);
	while (++i < (int)paths->size)
	{
		execve((char *)at(paths, i), cmd->argv, envp);
		if (errno != 2)
			break ;
	}
	delete_free(paths, &free);
	handle_errors(cmd, false, errno);
	return (1);
}

int			ft_exec_path(t_cmd *cmd, char **envp)
{
	execve(cmd->argv[0], cmd->argv, envp);
	handle_errors(cmd, true, errno);
	return (1);
}

int			exec_cmd(t_cmd *cmd)
{
	char	**env;

	env = extract_envp(g_config.envp);
	if (cmd->count > 0 && is_builtin(cmd->argv[0]))
		return (ft_exec_builtin(cmd));
	else if (cmd->count > 0 && is_path(cmd->argv[0]))
		return (ft_exec_path(cmd, env));
	else if (cmd->count > 0)
		return (ft_find_and_exec(cmd, env));
	free(env);
	return (0);
}
