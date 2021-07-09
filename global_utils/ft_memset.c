/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:55:01 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:57:48 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	char			*bb;

	i = 0;
	bb = b;
	while (i < len)
	{
		bb[i] = c;
		i++;
	}
	return (bb);
}
