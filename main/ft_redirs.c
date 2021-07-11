/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:29:22 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/11 20:04:34 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

int	save_stdinout(int *sout, int *sin)
{
	*sout = dup(1);
	*sin = dup(0);
	return (0);
}

void	restore_stdinout(t_type type, int *sout, int *sin)
{
	if (*sout != -1 && (type == RIGHT || type == RIGHT_APPEND || type == NONE))
	{
		dup2(*sout, 1);
	}
	if (*sin != -1 && (type == LEFT || type == HEREDOC || type == NONE))
	{
		dup2(*sin, 0);
	}
}

int	setup_redirection(t_type type, char *arg, int *sout, int *sin)
{
	int	fd;

	fd = -1;
	if (type == RIGHT)
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == RIGHT_APPEND)
		fd = open(arg, O_CREAT | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == HEREDOC)
	{
		int i = -1;
		while (++i < g_config.heredoc->size)
		{
			dprintf(2, "FFFF: %s\n", (char *)at(g_config.heredoc, i));
		}
		dprintf(2, "----------\n");
		//dprintf(2, "FNAME: %s - ARG: %s\n", (char *)at(g_config.heredoc, 0), arg);
		fd = open((char *)at(g_config.heredoc, 0), O_RDONLY);
		free(remove_at(g_config.heredoc, 0));
	}
	else if (type == LEFT)
		fd = open(arg, O_RDONLY);
	
	if (fd < 0)
		return (p_error(arg, NULL, NULL, 1));
	if (type == RIGHT || type == RIGHT_APPEND)
	{
		dup2(fd, 1);
		close(fd);
	}
	else if (type == LEFT || type == HEREDOC)
	{
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

int	setup_all_redirs(t_vector *redirs, int *sout, int *sin)
{
	int		i;
	int		code;
	t_redir	*redir;

	i = -1;
	code = 0;
	while (++i < (int)redirs->size)
	{
		redir = (t_redir *) at(redirs, i);
		restore_stdinout(redir->type, sout, sin);
		if (setup_redirection(redir->type, redir->arg, sout, sin) != 0)
			code = 1;
	}
	return (code);
}

void	delete_redir(void *redir)
{
	t_redir	*r;

	r = (t_redir *)redir;
	if (!r)
		return ;
	if (r->arg)
	{
		free(r->arg);
		r->arg = NULL;
	}
	free(r);
	r = NULL;
}
