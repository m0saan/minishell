/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:14:13 by moboustt          #+#    #+#             */
/*   Updated: 2021/07/06 21:08:23 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

static	int	ft_intlen(long x)
{
	if (x < 0)
		x = -x;
	if (x >= 1000000000)
		return (10);
	if (x >= 100000000)
		return (9);
	if (x >= 10000000)
		return (8);
	if (x >= 1000000)
		return (7);
	if (x >= 100000)
		return (6);
	if (x >= 10000)
		return (5);
	if (x >= 1000)
		return (4);
	if (x >= 100)
		return (3);
	if (x >= 10)
		return (2);
	return (1);
}

char *ft_itoa_neg(int n)
{
	int				i;
	unsigned		sign;
	int				n_len;
	char			*alloced_mem;

	i = 0;
	sign = -n;
	n_len = ft_intlen(n);
	alloced_mem = ft_malloc(n_len * sizeof(char) + 2);
	alloced_mem[0] = '-';
	while (n_len > i)
	{
		alloced_mem[n_len] = sign % 10 + '0';
		sign /= 10;
		n_len--;
	}
	alloced_mem[ft_intlen(n) + 1] = '\0';
	return ((char *)alloced_mem);
}

char		*ft_itoa(int n)
{
	int			i;
	int			n_len;
	char		*alloced_mem;

	i = 0;
	if (n < 0)
		return (ft_itoa_neg(n));
	n_len = ft_intlen(n);
	if (n >= 0)
		alloced_mem = ft_malloc(n_len * sizeof(char) + 1);
	while (n_len > 0)
	{
		alloced_mem[n_len - 1] = n % 10 + '0';
		n /= 10;
		n_len--;
		i++;
	}
	alloced_mem[i] = '\0';
	return (char *)(alloced_mem);
}
