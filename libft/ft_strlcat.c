/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:16:31 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/23 19:16:39 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srlen;
	size_t	dtlen;

	srlen = ft_strlen(src);
	dtlen = 0;
	if (dst == NULL && size == 0)
		return (srlen);
	while (*dst && size > 0)
	{
		dst++;
		dtlen++;
		size--;
	}
	while (*src && size-- > 1)
	{
		*dst++ = *src++;
	}
	if (size == 1 || *src == 0 || size == 0)
		*dst = '\0';
	return (dtlen + srlen);
}
