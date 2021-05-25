/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 22:54:10 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/29 22:41:04 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*nw_str;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (!f)
		return (NULL);
	if (!(nw_str = malloc(ft_strlen((char *)s) + 1)))
		return (NULL);
	nw_str = ft_strdup((char *)s);
	while (nw_str[i] != '\0')
	{
		nw_str[i] = f(i, (char)s[i]);
		i++;
	}
	return (nw_str);
}

