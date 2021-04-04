/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:30:30 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/04 15:47:34 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void ft_exit(char *msg, int code)
{
	if (msg)
		perror(msg);
	exit(code);
}

t_vector *new_vector()
{
	return new_vector_s(10);
}

t_vector *new_vector_s(t_size init_len)
{
	t_vector *new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
		ft_exit(ERR_MALLOC, 1);
	if (!(new_vector->data = (void **)malloc(sizeof(void *) * init_len)))
		ft_exit(ERR_MALLOC, 1);
	new_vector->capacity = init_len;
	new_vector->size = 0;
	new_vector->current = 0;
	return (new_vector);
}

t_vector *new_vector_from(t_vector *other)
{
	int i;
	t_size length;
	t_vector *new_vector;

	if (other == NULL || is_empty(other))
		ft_exit("Error\nVector is NULL/Empty", 1);
	length = other->size + other->size / 2;
	new_vector = new_vector_s(length);
	i = -1;
	while (++i < other->size)
		new_vector->data[new_vector->size++] = other->data[i];
	return (new_vector);
}

void *at(t_vector *this, size_t pos)
{
	if (this == NULL)
		ft_exit("Error\nAccessing items of a NULL Vector!", 1);
	if (pos >= this->size)
		ft_exit("Error\nIndex Out Of Bounds!", 1);
	return (this->data[pos]);
}

int is_empty(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNULL Vector!", 1);
	return (this->size == 0);
}

void insert(t_vector *this, void *item)
{
	void **old_data;
	size_t new_capacity;
	int i;

	if (this == NULL)
		ft_exit("Error\nInserting in a NULL Vector!", 1);
	if (this->size == this->capacity)
	{
		i = -1;
		new_capacity = this->size + this->size / 2;
		old_data = (void **)malloc(sizeof(void *) * new_capacity);
		while (++i < this->size)
			old_data[i] = this->data[i];
		free(this->data);
		this->data = old_data;
		this->capacity = new_capacity;
	}
	this->data[this->size++] = item;
}

void remove_item(t_vector *this, void *item)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (this->data[i] == item)
			remove_at(this, i);
	}
}

void remove_at(t_vector *this, t_size pos)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (is_empty(this))
		return;
	if (pos >= this->size)
		return;
	i = pos;
	while (i < this->size)
	{
		if (i + 1 < this->size)
			this->data[i] = this->data[i + 1];
		i++;
	}
	this->size--;
}

void clear(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	this->size = 0;
}

void delete (t_vector *this)
{
	int i;

	i = -1;
	if (this == NULL || this->data == NULL)
		ft_exit("Error\nNull Vector!", 1);
	free(this->data);
	free(this);
}

void *next(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (this->current < this->size)
		return (this->data[(this->current)++]);
	return (NULL);
}

t_pair *next_pair(t_vector *this)
{
	t_pair	*pair;
	void	*value1;
	void	*value2;

	if ((value1 = next(this)) == NULL)
		return (NULL);
	value2 = next(this);
	pair = (t_pair *)malloc(sizeof(t_pair));
	pair->get[0] = value1;
	pair->get[1] = value2;
	return (pair);
}

void *previous(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (--this->current >= 0)
		return (this->data[this->current]);
	return (NULL);
}

void *last(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(this))
		return (this->data[this->size - 1]);
	return (NULL);
}

void *first(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(this))
		return (this->data[0]);
	return (NULL);
}

int contains(t_vector *this, void *item)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (this->data[i] == item)
			return (true);
	}
	return (false);
}

int index_of(t_vector *this, void *item)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (this->data[i] == item)
			return (i);
	}
	return (-1);
}

t_size capacity(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	return (this->capacity);
}

void swap(t_vector *this, t_size pos1, t_size pos2)
{
	void *item;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos1 >= this->size || pos2 >= this->size || pos1 == pos2)
		return;
	item = this->data[pos1];
	this->data[pos1] = this->data[pos2];
	this->data[pos2] = item;
}

void move_to_last(t_vector *this, t_size pos)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos >= this->size)
		return;
	i = pos;
	while (i < this->size)
	{
		swap(this, i, i + 1);
		++i;
	}
}

void move_to_first(t_vector *this, t_size pos)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (pos >= this->size)
		return;
	i = pos;
	while (i - 1 >= 0)
	{
		swap(this, i, i - 1);
		--i;
	}
}

void display_vector(t_vector *this, char *(*to_string)(void *item))
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	printf("CAPACIITY: %lu\n", this->capacity);
	printf("SIZE:      %lu\n", this->size);
	printf("ITEMS:\n");
	i = -1;
	while (++i < this->size)
	{
		printf("%s", to_string(this->data[i]));
		if (i < this->size - 1)
			printf(", ");
	}
	printf("\n\n");
}

// void copy(t_vector *to, t_vector *from)
// {
// 	int i;
// 	if (from->size > (to->capacity - to->size))
// 		ft_exit("Error\nVector doesn't have enough Capacity for COPYING!", 1);
// 	i = -1;
// 	while (++i < from->size)
// 		to->data[to->size++] = from->data[i];
// }