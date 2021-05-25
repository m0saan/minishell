/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 01:06:52 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/17 22:54:11 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;
	int		ps;
	size_t	size;

	size = ft_strlen(s);
	ps = 0;
	i = 0;
	str = (char *)s;
	if (size == 0 && *s != c)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == c)
			ps = i;
		i++;
	}
	if (str[ps] == c)
		return (&str[ps]);
	return (NULL);
}
