/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:05:26 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 21:13:57 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*append_cmd_to_path(char *path, char *cmd)
{
	int			i;
	int			j;
	char		*out;
	const int	len = ft_strlen(path) + ft_strlen(cmd) + 2;

	i = 0;
	j = 0;
	out = (char *)ft_malloc(len * sizeof(char));
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

	path = ft_substr(path_str, *start, end);
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

t_bool		is_path(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			return (true);
	return (false);
}
