/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 20:12:52 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 20:33:15 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

char	*ft_substr(char *str, int from, int to)
{
	int		i;
	int		len;
	char	*sub;

	i = 0;
	if (!str)
		return (NULL);
	len = (int) ft_strlen(str);
	if (from < 0 || from >= to || from >= len || to > len)
		return (NULL);
	sub = (char *)ft_malloc((to - from + 1) * sizeof(char));
	while (from < to)
		sub[i++] = str[from++];
	sub[i] = '\0';
	return (sub);
}
