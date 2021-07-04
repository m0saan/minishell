/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:25:17 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:43:22 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_utility.h"
#include "../include/global_utils.h"
#include "../include/minishell.h"



void	update_status_code(int code)
{
	if (code >= 0)
		set_var2(g_envp, "?", ft_itoa(code), false);
	else
		set_var2(g_envp, "?", ft_itoa(WEXITSTATUS(g_status)), false);
}


