/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:30:30 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/01 19:14:20 by ehakam           ###   ########.fr       */
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

	if (vector == NULL || is_empty(vector))
		ft_exit("Error\nvector shouldn't be null or empty!", 1);
	length = vector->size + vector->size / 2;
	new_vector = new_vector_s(length);
	copy(vector, new_vector);
	return (new_vector);
}

void copy(t_vector *from, t_vector *to)
{
	int i;

	if (from->size > (to->length - to->size))
		ft_exit("Error\nVector doesn't have enough Capacity for COPYING!", 1);
	i = -1;
	while (++i < from->size)
		insert(to, from->data[i]);
}

void *at(t_vector *vector, size_t pos)
{
	if (vector == NULL)
		ft_exit("Error\nAccessing items of a NULL Vector!", 1);
	if (pos >= vector->size)
		ft_exit("Error\nIndex Out Of Bounds!", 1);
	return (vector->data[pos]);
}

int is_empty(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNULL Vector!", 1);
	return (vector->size == 0);
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
		delete (&temp);
	}
	vector->data[vector->size++] = item;
}

void remove_item(t_vector *vector, void *item)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < vector->size)
	{
		if (vector->data[i] == item)
			remove_at(vector, i);
	}
}

void remove_at(t_vector *vector, t_size pos)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (is_empty(vector))
		return;
	if (pos >= vector->size)
		return;
	i = pos;
	while (i < vector->size)
	{
		if (i + 1 < vector->size)
			vector->data[i] = vector->data[i + 1];
		i++;
	}
	vector->size--;
}

void clear(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	vector->size = 0;
}

void delete (t_vector **vector)
{
	int i;

	i = -1;
	if (vector == NULL || (*vector)->data == NULL)
		ft_exit("Error\nNull Vector!", 1);
	free((*vector)->data);
	free(*vector);
}

void *next(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (++vector->current < vector->size)
		return (vector->data[vector->current]);
	return (NULL);
}

void *previous(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (--vector->current >= 0)
		return (vector->data[vector->current]);
	return (NULL);
}

void *last(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(vector))
		return (vector->data[vector->size - 1]);
	return (NULL);
}

void *first(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(vector))
		return (vector->data[0]);
	return (NULL);
}

int contains(t_vector *vector, void *item)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < vector->size)
	{
		if (vector->data[i] == item)
			return (true);
	}
	return (false);
}

int index_of(t_vector *vector, void *item)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < vector->size)
	{
		if (vector->data[i] == item)
			return (i);
	}
	return (-1);
}

t_size capacity(t_vector *vector)
{
	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	return (vector->length);
}

void swap(t_vector *vector, t_size pos1, t_size pos2)
{
	void *item;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos1 >= vector->size || pos2 >= vector->size || pos1 == pos2)
		return;
	item = vector->data[pos1];
	vector->data[pos1] = vector->data[pos2];
	vector->data[pos2] = item;
}

void move_to_last(t_vector *vector, t_size pos)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos >= vector->size)
		return;
	i = pos;
	while (i < vector->size)
	{
		swap(vector, i, i + 1);
		++i;
	}
}

void move_to_first(t_vector *vector, t_size pos)
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos >= vector->size)
		return;
	i = pos;
	while (i - 1 >= 0)
	{
		swap(vector, i, i - 1);
		++i;
	}
}

void display_vector(t_vector *vector, void (*print)(void *item))
{
	int i;

	if (vector == NULL)
		ft_exit("Error\nNull Vector!", 1);
	printf("CAPACIITY: %lu\n", vector->length);
	printf("SIZE:      %lu\n", vector->size);
	printf("ITEMS:\n");
	i = -1;
	while (++i < vector->size)
	{
		print(vector->data[i]);
		if (i < vector->size - 1)
			printf(", ");
	}
	printf("\n\n");
}
