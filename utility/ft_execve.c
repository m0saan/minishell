/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:14:12 by ehakam            #+#    #+#             */
/*   Updated: 2021/05/03 12:46:51 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		ft_exec_builtin(char *cmd, int ac, char **av)
{
	if (strcmp(cmd, "cd") == 0);
	else if (strcmp(cmd, "echo") == 0);
	else if (strcmp(cmd, "export") == 0);
	else if (strcmp(cmd, "env") == 0);
	else if (strcmp(cmd, "exit") == 0);
	else if (strcmp(cmd, "pwd") == 0);
	else if (strcmp(cmd, "unset") == 0);
	return (0);
}

int main()
{
	char *pp = "/Users/ehakam/.brew/bin:/Users/ehakam/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/ehakam/.brew/bin:/goinfre/ehakam/Android/flutter_sdk/flutter/bin:/goinfre/ehakam/Android/flutter_sdk/flutter/bin";
	char *pp2 = "DODO";
	t_vector *p = get_paths(pp, "ls");

	p->display(p, to_str);
	return (0);
}
