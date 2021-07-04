/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:21:11 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:43:09 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	ft_memset(command, 0, sizeof(t_cmd));
	command->redirs = new_vector();
	return (command);
}