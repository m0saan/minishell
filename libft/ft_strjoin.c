/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 22:15:00 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/18 22:16:09 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			s1_len;
	int			s2_len;
	char		*new_alloc;
	int			i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	if (!(new_alloc = malloc(s1_len + s2_len + 1)))
		return (NULL);
	while (s1[i])
	{
		new_alloc[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		new_alloc[i] = s2[i - s1_len];
		i++;
	}
	new_alloc[i] = '\0';
	return ((char *)new_alloc);
}
