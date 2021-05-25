/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 01:13:58 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/16 01:15:36 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_memcmp_stp(const void *s1, const void *s2, size_t n)
{
	unsigned int			i;
	unsigned char			*str1;
	unsigned char			*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] == str2[i] && (str1[i] || str2[i]) != '\0')
		i++;
	if (str1[i] != str2[i] && i < n && (str1[i] || str2[i]) != '\0')
		return (str1[i] - str2[i]);
	return (0);
}

int				ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int cmp;

	cmp = ft_memcmp_stp(str1, str2, n);
	if (cmp != 0)
		return (cmp);
	return (0);
}
