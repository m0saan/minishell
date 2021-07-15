/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:09:39 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:12:20 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(t_redir *redir, int index)
{
	char	*fname;

	fname = strjoin_c("/tmp/.HEREDOC", index++ + 48, false);
	signal(SIGINT, signal_handler_heredoc);
	waitpid(open_heredoc(fname, redir->arg), &g_config.status, 0);
	g_config.is_forked = false;
	signal(SIGINT, signal_handler_parent);
	free(redir->arg);
	redir->arg = fname;
	if (WEXITSTATUS(g_config.status) == 1)
	{
		update_status_code(1);
		return (1);
	}
	return (0);
}

int	handle_digit(char **new_buf, char *buf, int idx, int start)
{
	start = 0;
	if (buf[idx++] == '0')
		*new_buf = strjoin_s(*new_buf, "minishell", true);
	else
		*new_buf = strjoin_s(*new_buf, "", true);
	return (idx);
}

int	handle_alpha(char **new_buf, char *buf, int idx, int start)
{
	char	*key;

	while (ft_isalnum(buf[idx]) || buf[idx] == '_')
		++idx;
	key = ft_substr(buf, start, idx);
	if (key)
	{
		if (get_var(g_config.envp, key))
			*new_buf = strjoin_s(*new_buf, get_var(g_config.envp, key), true);
		else
			*new_buf = strjoin_s(*new_buf, "", true);
		free(key);
	}
	return (idx);
}

int	handle_special(char **new_buf, char *buf, int idx, int start)
{
	start = 0;
	buf = NULL;
	*new_buf = strjoin_s(*new_buf, get_var(g_config.envp, "?"), true);
	return (++idx);
}

int	handle_var(char **new_buf, char *buf, int idx, int start)
{
	if (ft_isdigit(buf[idx]))
	{
		idx = handle_digit(new_buf, buf, idx, start);
	}
	else if (ft_isalpha(buf[idx]) || buf[idx] == '_')
	{
		idx = handle_alpha(new_buf, buf, idx, start);
	}
	else if (buf[idx] == '?')
	{
		idx = handle_special(new_buf, buf, idx, start);
	}
	return (idx);
}
