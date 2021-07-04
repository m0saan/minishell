/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:14:12 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:45:58 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_utility.h"
#include "../include/minishell.h"
#include "../include/global_utils.h"

t_bool		is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "cd") == 0);
}

char		*append_cmd_to_path(char *path, char *cmd)
{
	int			i;
	int			j;
	char		*out;
	const int	len = ft_strlen(path) + strlen(cmd) + 2;

	i = 0;
	j = 0;
	out = (char *)malloc(len * sizeof(char));
	if (!out)
		exit(1);
	while (path[i])
		out[j++] = path[i++];
	out[j++] = '/';
	i = 0;
	while (cmd[i])
		out[j++] = cmd[i++];
	out[j] = '\0';
	free(path);
	return (out);
}

char		*get_path(char *path_str, char *cmd, int *start, int end)
{
	char	*path;

	path = ft_substr2(path_str, *start, end);
	if (path != NULL)
		path = append_cmd_to_path(path, cmd);
	else
		path = append_cmd_to_path(ft_strdup("."), cmd);
	*start = end + 1;
	return (path);
}

t_vector	*get_paths(char *path_str, char *cmd)
{
	t_vector	*paths;
	int			end;
	int			start;

	end = -1;
	start = 0;
	paths = new_vector_s(30);
	if (!paths)
		exit(1);
	if (path_str != NULL && path_str[0] != '\0')
	{
		while (path_str[++end])
			if (path_str[end] == ':')
				insert(paths, get_path(path_str, cmd, &start, end));
		insert(paths, get_path(path_str, cmd, &start, end));
	}
	else
		insert(paths, append_cmd_to_path(ft_strdup("."), cmd));
	return (paths);
}

int			ft_exec_builtin(t_cmd *cmd)
{
	//dprintf(2, "ft_exec_builtin\n");
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd->count, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->count, cmd->argv));
	return (0);
}

void		handle_errors(t_cmd *cmd, t_bool ispath, int errno_)
{
	struct stat dir_stat;

	if (ispath && stat(cmd->argv[0], &dir_stat) == 0
		&& S_ISDIR(dir_stat.st_mode))
		exit(p_error(cmd->argv[0], NULL, "is a directory", 126));
	if (errno_ == 13)
		exit(p_error(cmd->argv[0], NULL, NULL, 126));
	else if (errno_ == 8)
		exit(p_error(cmd->argv[0], NULL, NULL, 1));
	else if (ispath || get_var(g_envp, "PATH") == NULL)
		exit(p_error(cmd->argv[0], NULL, NULL, 127));
	else
		exit(p_error(cmd->argv[0], NULL, "command not found", 127));
}

int			ft_find_and_exec(t_cmd *cmd, char **envp)
{
	t_vector	*paths;
	int			i;

	i = -1;
	paths = get_paths(get_var(g_envp, "PATH"), cmd->argv[0]);
	while (++i < (int)paths->size)
	{
		execve((char *)at(paths, i), cmd->argv, envp);
		if (errno != 2)
			break ;
	}
	delete(paths);
	handle_errors(cmd, false, errno);
	return (1);
}

int			ft_exec_path(t_cmd *cmd, char **envp)
{
	execve(cmd->argv[0], cmd->argv, envp);
	handle_errors(cmd, true, errno);
	return (1);
}

t_bool	is_path(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			return (true);
	return (false);
}

int		exec_cmd(t_cmd *cmd)
{
	//dprintf(2, "exec_cmd\n");
	char	**env;

	env = extract_envp(g_envp);
	if (cmd->count > 0 && is_builtin(cmd->argv[0]))
		return (ft_exec_builtin(cmd));
	else if (cmd->count > 0 && is_path(cmd->argv[0]))
		return (ft_exec_path(cmd, env));
	else if (cmd->count > 0)
		return (ft_find_and_exec(cmd, env));
	free(env);
	return (0);
}
