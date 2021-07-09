/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:44:58 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:38:06 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

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
		if (buffer[end] == '$'
			&& (ft_isalnum(buffer[end + 1]) || ft_isspecial(buffer[end + 1])))
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

t_bool	read_write(int fd, char *delim)
{
	char	*buffer;
	t_bool	exit_by_delim;

	exit_by_delim = false;
	write(2, "> ", 2);
	while (true)
	{
		if (get_next_line(&buffer) <= 0)
			break ;
		if (ft_strcmp(delim, buffer) == 0)
		{
			exit_by_delim = true;
			break ;
		}
		if (buffer && buffer[0] && index_of_c(buffer, '$') != -1)
			buffer = replace_var(buffer);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		write(2, "> ", 2);
		free(buffer);
	}
	if (buffer)
		free(buffer);
	return (exit_by_delim);
}

int	open_heredoc(char *delim)
{
	int		fd;
	t_bool	exit_by_delim;

	fd = open("/tmp/.HEREDOC", O_CREAT | O_TRUNC | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		exit(p_error("/tmp/.HEREDOC", NULL, NULL, 1));
	exit_by_delim = read_write(fd, delim);
	close(fd);
	if (!exit_by_delim)
		p_error("warning", "here-document delimited by end-of-file wanted",
			delim, 0);
	fd = open("/tmp/.HEREDOC", O_RDONLY);
	return (fd);
}
