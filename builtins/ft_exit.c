/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:16:50 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 19:21:17 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_builtin.h"
#include "../include/error.h"
#include "../include/minishell.h"

int	ft_exit(int ac, char **av)
{
	const char		*err_msg = "too many arguments";
	unsigned char	code;

	if (ac < 2)
		exit(0);
	code = (unsigned char)ft_atol_err(av[1]);
	if (ac > 2)
		return (p_error("exit", NULL, err_msg, 1));
	exit(code);
}
