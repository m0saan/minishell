/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:53:00 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/17 22:22:15 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		sz;

	i = 0;
	sz = ft_strlen(s);
	if (sz == 0 && *s != c)
		return (NULL);
	if (!c)
	{
		while (*s)
			s++;
		return ((char*)s);
	}
	if (!*s)
		return ((char*)s);
	while (sz > i)
	{
		if (s[i] == c)
			return (char *)(s + i);
		i++;
	}
	return (NULL);
}
