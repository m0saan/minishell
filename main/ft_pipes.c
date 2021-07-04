/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:27:51 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:43:39 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"
#include "../include/minishell.h"

int		get_position(t_size size, int index)
{
	if (size == 1)
		return (IS_FIRSTLAST);
	if (index == 0)
		return (IS_FIRST);
	if (index == ((int)size - 1))
		return (IS_LAST);
	return (IS_MIDDLE);
}

void	setup_pipes(int fd[][2], int position, int index)
{
	const int prev_idx = index - 1;

	if (position == IS_FIRST)
	{
		dup2(fd[index][1], 1);
		close(fd[index][0]);
	}
	else if (position == IS_MIDDLE)
	{
		dup2(fd[prev_idx][0], 0);
		dup2(fd[index][1], 1);
		close(fd[index][0]);
		close(fd[prev_idx][1]);
	}
	else if (position == IS_LAST)
	{
		dup2(fd[prev_idx][0], 0);
		close(fd[prev_idx][1]);
		close(fd[index][1]);
		close(fd[index][0]);
	}
	close(fd[index][1]);
	close(fd[index][0]);
}

void	close_pipes(int fd[][2], int pos, int index)
{
	if (pos == IS_FIRST)
		close(fd[index][1]);
	if (pos == IS_MIDDLE)
	{
		close(fd[index - 1][0]);
		close(fd[index][1]);
	}
	if (pos == IS_LAST)
		close(fd[index - 1][0]);
}
