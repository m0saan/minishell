/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:51:45 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:57:37 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

int	ft_atoi(char *str)
{
	int		i;
	int		n;
	long	r;

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
		r = r * 10 + (str[i++] - '0');
	return (r * n);
}
