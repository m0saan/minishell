/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:14:12 by ehakam            #+#    #+#             */
/*   Updated: 2021/05/23 19:38:26 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../commands/ft_buildin.h"

char *to_str(void *item)
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

t_vector *get_paths(char *path_str, char *cmd)
{
	t_vector *pv;
	char *path;
	int end;
	int start;

	end = -1;
	start = 0;
	pv = new_vector_s(20);
	while (path_str[++end])
	{
		if (path_str[end] == ':')
		{
			path = ft_substr(path_str, start, end);
			if (path != NULL)
				pv->insert(pv, append_cmd_to_path(path, cmd));
			start = end + 1;
		}
	}
	path = ft_substr(path_str, start, end);
	if (path != NULL)
		pv->insert(pv, append_cmd_to_path(path, cmd));
	return (pv);
}

int		ft_exec_builtin(t_cmd *cmd, char **envp)
{
	dprintf(2, "INFO: Exec buildin!\n");
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
	while (++i < paths->size)
	{
		execve((char *)paths->at(paths, i), cmd->argv, envp);
		dprintf(2, "INFO: TESTING PATH(%s) FAILED!\n", paths->at(paths, i));
	}
	dprintf(2, "ERROR: Command Not Found!\n");
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
		ft_exec_builtin(cmd, env);
	}
	else if (is_path(cmd->argv[0]))
	{
		dprintf(2, "INFO: Exec Path '%s'\n", cmd->argv[0]);
		execve(cmd->argv[0], cmd->argv, env);
		dprintf(2, "ERROR: Cmd '%s' Doesn't exist!\n", cmd->argv[0]);
	}
	else
	{
		ft_find_and_exec(cmd, env);
	}
	return (0);
}

int		fill_envp2(char **envp)
{
	int		i;

	i = -1;
	if (!envp)
		return (1);
	g_envp = new_vector();
	while (envp[++i] != NULL)
	{
		g_envp->insert(g_envp, split_key_value_v(envp[i]));
	}
	return (0);
}

t_cmd *create_cmd(char *arg1, char *arg2, int count)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->argv[0] = arg1;
	cmd->argv[1] = arg2;
	cmd->argv[2] = NULL;
	cmd->count = count;
	cmd->redirs = new_vector();
	return (cmd);
}

char *to_string(void *item)
{
	t_var *var = (t_var *)item;
	char *str = malloc(200 * sizeof(char));
	
	strcat(str, "\n");
	strcat(str, "KEY: ");
	strcat(str, var->key);
	strcat(str, " ##\t\t\t\t\t VALUE: ");
	strcat(str, var->value != NULL ? var->value : "<NULL>");
	// char *str3 = strdup(var->value != NULL ? var->value : "none");
	return (str);
}

int main(int ac, char **av, char **env)
{
	fill_envp2(env);

	pid_t pid = fork();

	t_cmd *cmd = create_cmd("echo", "hakam", 2);

	if (pid == 0) {
		exec_cmd(cmd);
	}

	wait(&pid);
	
	return (0);
}
