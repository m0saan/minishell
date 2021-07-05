/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:29:22 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:43:54 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

int		save_stdinout(t_type type, int fd, int *sout, int *sin)
{
	if (type == RIGHT || type == RIGHT_APPEND)
	{
		*sout = dup(1);
		dup2(fd, 1);
		close(fd);
	}
	else if (type == LEFT || type == HEREDOC)
	{
		*sin = dup(0);
		dup2(fd, 0);
		close(fd);
	}
	return (0);
}

void	restore_stdinout(int sout, int sin)
{
	if (sout != -1)
	{
		dup2(sout, 1);
		close(sout);
	}
	if (sin != -1)
	{
		dup2(sin, 0);
		close(sin);
	}
}

int		setup_redirection(t_type type, char *arg, int *sout, int *sin)
{
	int fd;

	fd = -1;
	if (type == RIGHT)
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == RIGHT_APPEND)
		fd = open(arg, O_CREAT | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == HEREDOC) {
		fd = open_heredoc(arg);
	}
	else if (type == LEFT)
		fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (p_error(arg, NULL, NULL, 1));
	save_stdinout(type, fd, sout, sin);
	return (0);
}

int		setup_all_redirs(t_vector *redirs, int *sout, int *sin)
{
	int i;
	int code;
	t_redir *redir;

	i = -1;
	code = 0;
	while (++i < (int)redirs->size)
	{
		restore_stdinout(*sout, *sin);
		redir = (t_redir *) at(redirs, i);
		if (setup_redirection(redir->type, redir->arg, sout, sin) != 0)
			code = 1;
	}
	return (code);
}

void	delete_redir(void *redir)
{
	t_redir *r;

	r = (t_redir *)redir;
	if (!r)
		return ;
	if (r->arg)
	{
		free(r->arg);
		r->arg = NULL;
	}
	dprintf(2, "FREED REDIR\n");
	free(r);
	r = NULL;
}

