/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 00:56:03 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/28 19:06:02 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	// if (haystack == NULL)
	// 	return (NULL);
	// if (*haystack == '\0')
	// 	return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
// #include <stdio.h>
// int main(void)
// {
// 	printf("my = %s\n", ft_strnstr("", "", 40));
// 	//printf("or = %s\n", strnstr("", "", 40));
// 	return 0;
// }