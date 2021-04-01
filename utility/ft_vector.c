/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:30:30 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/01 16:20:44 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void ft_exit(char *msg, int code)
{
	if (msg)
		perror(msg);
	exit(code);
}

t_vector *new_vector_s(t_size init_len)
{
	t_vector *new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
		ft_exit(ERR_MALLOC, 1);
	if (!(new_vector->data = (void **)malloc(sizeof(void *) * init_len)))
		ft_exit(ERR_MALLOC, 1);
	new_vector->length = init_len;
	new_vector->size = 0;
	new_vector->is_empty = true;
	new_vector->current = 0;
	return (new_vector);
}

t_vector *new_vector()
{
	return new_vector_s(10);
}

t_vector *new_vector_from(t_vector *vector)
{
	t_size length;
	t_vector *new_vector;

	if (vector == NULL || vector->is_empty)
		ft_exit("Error\nvector shouldn't be null or empty!", 1);
	length = vector->size + vector->size / 2;
	new_vector = new_vector_s(length);
	copy(vector, new_vector);
	return (new_vector);
}

void	copy(t_vector *from, t_vector *to)
{
	int i;

	if (from->size > (to->length - to->size))
		ft_exit("Error\nVector doesn't have enough Capacity for COPYING!", 1);
	i = -1;
	while (++i < from->size)
		insert(to, at(from, i));
}

void	*at(t_vector *vector, size_t pos)
{
	if (vector == NULL)
		ft_exit("Error\nAccessing items of a NULL Vector!", 1);
	if (pos >= vector->size)
		ft_exit("Error\nIndex Out Of Bounds!", 1);
	return (vector->data[pos]);
}

void insert(t_vector *vector, void *item)
{
	t_vector *temp;

	if (vector == NULL)
		ft_exit("Error\nInserting in a NULL Vector!", 1);
	if (vector->size == vector->length)
	{
		temp = vector;
		vector = new_vector_from(vector);
	}
}
