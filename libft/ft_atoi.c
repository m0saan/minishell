/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:07:48 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/28 19:15:19 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_res(char const *str, int i)
{
	long	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

int			ft_atoi(const char *s)
{
	int		i;
	int		rc;
	char	*str;

	i = 0;
	rc = 0;
	str = (char *)s;
	if (!*str)
		return (0);
	while ((str[i] >= 0 && str[i] <= 26) || (str[i] >= 28 && str[i] <= 32))
		i++;
	if (str[i] == '\e')
		return (0);
	if (str[i] == '-')
		rc = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (rc == 1)
		return (-ft_res(str, i));
	return (ft_res(str, i));
}
