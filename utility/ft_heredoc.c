/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:44:58 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/03 21:47:19 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utility.h"
#include "../global_utils/global_utils.h"
#include "../minishell.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		ret;

	buffer = (char *)malloc(2);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	ret = 1;
	while (ret)
	{
		ret = read(0, buffer, 1);
		if (ret)
		{
			if (buffer[0] == '\n' || ret == EOF)
				break ;
			*line = strjoin_c(*line, buffer[0], true);
		}
	}
	free(buffer);
	return (ret);
}

int	handle_var(char **new_buf, char *buf, int idx, int start)
{
	char	*key;

	if (ft_isdigit(buf[idx]))
	{
		if (buf[idx++] == '0')
			*new_buf = strjoin_s(*new_buf, "minishell", true);
		else
			*new_buf = strjoin_s(*new_buf, "", true);
	}
	else if (ft_isalpha(buf[idx]) || buf[idx] == '_')
	{
		while (ft_isalnum(buf[idx]) || buf[idx] == '_')
			++idx;
		key = ft_substr2(buf, start, idx);
		if (key)
		{
			if (get_var(g_envp, key))
				*new_buf = strjoin_s(*new_buf, get_var(g_envp, key), true);
			else
				*new_buf = strjoin_s(*new_buf, "", true);
			free(key);
		}
	}
	return (idx);
}

char	*replace_var(char *buffer)
{
	char	*new_buff;
	t_bool	is_var;
	int		start;
	int		end;

	end = 0;
	new_buff = NULL;
	is_var = false;
	while (buffer[end])
	{
		if (buffer[end] == '$' &&
			(ft_isalnum(buffer[end + 1]) || buffer[end + 1] == '_'))
			is_var = true;
		if (!is_var && buffer[end] != '\0')
		{
			new_buff = strjoin_c(new_buff, buffer[end++], true);
			continue ;
		}
		start = ++end;
		end = handle_var(&new_buff, buffer, end, start);
		is_var = false;
	}
	free(buffer);
	return (new_buff);
}

int	open_heredoc(char *delim)
{
	int		fd;
	char	*buffer;
	t_bool	exit_by_delim;

	exit_by_delim = false;
	fd = open("/tmp/.HEREDOC", O_CREAT | O_TRUNC | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(2, "> ", 2);
	while (true)
	{
		if (get_next_line(&buffer) <= 0)
			break ;
		if (strcmp(delim, buffer) == 0)
		{
			exit_by_delim = true;
			break ;
		}
		buffer = replace_var(buffer);
		write(fd, buffer, strlen(buffer));
		write(fd, "\n", 1);
		write(2, "> ", 2);
	}
	close(fd);
	if (!exit_by_delim)
		p_error("warning", "here-document delimited by end-of-file wanted",
			delim, 0);
	fd = open("/tmp/.HEREDOC", O_RDONLY);
	return (fd);
}
