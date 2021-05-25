/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 22:53:10 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/19 17:24:13 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_char_to_check(char *set, int c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		st;
	int		ed;
	char	*new_str_alloced;

	i = 0;
	st = 0;
	if (!s1 || !set)
		return (NULL);
	ed = ft_strlen((char *)s1) - 1;
	while (ft_char_to_check((char *)set, s1[st]) != 0 && s1[i] != '\0')
		st++;
	while (ft_char_to_check((char *)set, s1[ed]) != 0 && ed > 0)
		ed--;
	if (ed == 0)
		new_str_alloced = malloc(1);
	else
	{
		if (!(new_str_alloced = malloc(ed - st + 2)))
			return (NULL);
	}
	while (ed >= st)
		new_str_alloced[i++] = s1[st++];
	new_str_alloced[i] = '\0';
	return (new_str_alloced);
}
