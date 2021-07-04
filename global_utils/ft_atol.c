/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 19:20:09 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 19:22:21 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

long long	ft_atol_err(char *str)
{
	int			i;
	int			n;
	long long	r;
	const char	*err_msg = "numeric argument required";

	i = 0;
	r = 0;
	n = 1;
	while (str[i] > 0 && str[i] < 33 && str[i] != 27)
		i++;
	if (str[i] == '-' && ++i)
		n = -1;
	else if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i++] - '0');
		if ((n == 1 && r > MAXVAL) || (n == -1 && r > MAXVAL))
			exit(p_error("exit", str, err_msg, (unsigned char)(r * n)));
	}
	while (str[i] > 0 && str[i] < 33 && str[i] != 27)
		i++;
	if (str[i] != '\0')
		exit(p_error("exit", str, err_msg, 255));
	return (r * n);
}
