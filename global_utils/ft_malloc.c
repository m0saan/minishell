/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:29:20 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 21:00:44 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/global_utils.h"

void	*ft_malloc(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		exit(1);
	return (alloc);
}
