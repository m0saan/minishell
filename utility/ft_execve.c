/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:14:12 by ehakam            #+#    #+#             */
/*   Updated: 2021/06/02 18:06:32 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*to_str(void *item)
{
	printf("\n");
	return ((char *)item);
}

t_bool	is_builtin(char *cmd)
{
	return (strcmp(cmd, "echo") == 0 || strcmp(cmd, "export") == 0
			|| strcmp(cmd, "env") == 0 || strcmp(cmd, "exit") == 0
			|| strcmp(cmd, "pwd") == 0 || strcmp(cmd, "unset") == 0
			|| strcmp(cmd, "cd") == 0);
}

char	*append_cmd_to_path(char *path, char *cmd)
{
	int		i;
	int		j;
	char	*out;
	const	int len = strlen(path) + strlen(cmd) + 2;
	
	i = 0;
	j = 0;
	out = (char *)malloc(len * sizeof(char));
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

t_vector*get_paths(char *path_str, char *cmd)
{
	t_vector *pv;
	char *path;
	int end;
	int start;

	end = -1;
	start = 0;
	pv = new_vector_s(20);
	if (path_str != NULL && path_str[0] != '\0')
	{
		if (path_str[0] == ':')
			pv->insert(pv, append_cmd_to_path(strdup("."), cmd));
		while (path_str[++end])
		{
			if (path_str[end] == ':')
			{
				path = ft_substr2(path_str, start, end);
				if (path != NULL)
					pv->insert(pv, append_cmd_to_path(path, cmd));
				else
					pv->insert(pv, append_cmd_to_path(strdup("."), cmd));
				start = end + 1;
			}
		}
		path = ft_substr2(path_str, start, end);
		if (path != NULL)
			pv->insert(pv, append_cmd_to_path(path, cmd));
		else
			pv->insert(pv, append_cmd_to_path(strdup("."), cmd));
	}
	else
		pv->insert(pv, append_cmd_to_path(strdup("."), cmd));
	return (pv);
}

int		ft_exec_builtin(t_cmd *cmd, char **envp)
{
	//dprintf(2, "\033[0;32mINFO: Exec builtin!\033[0m\n");
	if (strcmp(cmd->argv[0], "cd") == 0)
		ft_cd(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "echo") == 0)
		ft_echo(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "export") == 0)
		ft_export(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "env") == 0)
		ft_env(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "exit") == 0)
		ft_exits(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "pwd") == 0)
		ft_pwd(cmd->count, cmd->argv);
	else if (strcmp(cmd->argv[0], "unset") == 0)
		ft_unset(cmd->count, cmd->argv);
	return (0);
}

int		ft_find_and_exec(t_cmd *cmd, char **envp) {
	t_vector	*paths = get_paths(get_var(g_envp, "PATH"), cmd->argv[0]);
	int		i;

	i = -1;
	if (paths == NULL)
	{
		dprintf(2, "\033[0;31mERROR: No such file!\033[0m\n");
		return 1;
	}
	while (++i < paths->size)
	{
		execve((char *)paths->at(paths, i), cmd->argv, envp);
		// dprintf(2, "\033[0;32mINFO: TESTING PATH(%s) FAILED!\033[0m\n", paths->at(paths, i));
	}
	dprintf(2, "\033[0;31mERROR: Command Not Found!\033[0m\n");
	return 1;
}

t_bool	is_path(char *cmd) {
	int		i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			return true;
	return (false);	
}

int		exec_cmd(t_cmd *cmd) {
	char	**env = extract_envp(g_envp);

	if (is_builtin(cmd->argv[0]))
	{
		return (ft_exec_builtin(cmd, env));
	}
	else if (is_path(cmd->argv[0]))
	{
		execve(cmd->argv[0], cmd->argv, env);
		ft_exit("NAAAAAH!", 33);
		return 33;
	}
	else
	{
		return (ft_find_and_exec(cmd, env));
	}
}

