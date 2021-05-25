/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:45:58 by moboustt          #+#    #+#             */
/*   Updated: 2019/10/15 23:46:33 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dt;
	unsigned char	*sc;
	size_t			i;

	dt = (unsigned char *)dst;
	sc = (unsigned char *)src;
	i = len - 1;
	if ((dst == NULL && src == NULL) || len == 0)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (i > 0)
		{
			dt[i] = sc[i];
			i--;
		}
		dt[i] = sc[i];
	}
	return (dst);
}
