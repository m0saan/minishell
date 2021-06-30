/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:16:50 by ehakam            #+#    #+#             */
/*   Updated: 2021/06/30 22:04:31 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"

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

int	ft_exits(int ac, char **av)
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
