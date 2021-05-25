/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:56:34 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/21 15:56:46 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub_str;
	size_t		len_s;

	i = 0;
	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	if (!(sub_str = malloc(len * sizeof(char) + 1)))
		return (NULL);
	while (s[start] != '\0' && i < len && start < len_s)
	{
		sub_str[i] = *(unsigned char *)(s + start);
		start++;
		i++;
	}
	sub_str[i] = '\0';
	return (char *)(sub_str);
}
