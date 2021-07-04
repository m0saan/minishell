/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:54:03 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:54:25 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

char	*strjoin_s(char *s, char *s2, t_bool free_)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	if (s2)
		i += ft_strlen(s2);
	str = (char *)malloc(i + 1);
	i = 0;
	j = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (free_)
		free(s);
	return (str);
}

char	*strjoin_c(char *s, char c, t_bool free_)
{
	int		i;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	str = (char *)malloc(i + 2);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	str[i] = c;
	str[++i] = '\0';
	if (free_)
		free(s);
	return (str);
}
