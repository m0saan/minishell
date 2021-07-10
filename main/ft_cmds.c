/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:21:11 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/10 21:48:52 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*command;

	command = ft_malloc(sizeof(t_cmd));
	ft_memset(command, 0, sizeof(t_cmd));
	command->redirs = new_vector();
	return (command);
}

void	delete_cmd(void *cmd)
{
	t_cmd	*c;

	c = (t_cmd *)cmd;
	if (!c)
		return ;
	while (--(c->count) >= 0)
	{
		free(c->argv[c->count]);
	}
	delete_free(c->redirs, &delete_redir);
	free(c);
	c = NULL;
}
