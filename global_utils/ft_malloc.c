/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:29:20 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 20:30:42 by ehakam           ###   ########.fr       */
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
// void *my_malloc(size_t size, const char *file, int line, const char *func)
// {
// 	void *p = malloc(size);
// 	printf("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);
// 	insert(g_config.x_malloc_vec, p);
// 	return p;
// }