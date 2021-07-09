/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:07:58 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/06 21:11:30 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_vector.h"

int	is_empty(t_vector *this)
{
	if (this == NULL)
		exit(1);
	return (this->size == 0);
}

void	insert(t_vector *this, void *item)
{
	void	**old_data;
	size_t	new_capacity;
	int		i;

	if (this == NULL)
		exit(1);
	if (this->size == this->capacity - 1)
	{
		i = -1;
		new_capacity = this->capacity + this->capacity / 2;
		old_data = (void **)ft_malloc(sizeof(void *) * new_capacity);
		while (++i < (int)this->size)
			old_data[i] = this->data[i];
		free(this->data);
		this->data = old_data;
		this->capacity = new_capacity;
	}
	this->data[this->size++] = item;
	this->data[this->size] = NULL;
}

void	*remove_at(t_vector *this, int pos)
{
	int		i;
	void	*item;

	if (this == NULL)
		exit(EXIT_FAILURE);
	if (is_empty(this))
		return (NULL);
	if (pos >= this->size)
		return (NULL);
	i = pos;
	item = at(this, pos);
	while (i < (int) this->size)
	{
		if (i + 1 < (int) this->size)
			this->data[i] = this->data[i + 1];
		i++;
	}
	this->size--;
	this->data[this->size] = NULL;
	return (item);
}

void	delete(t_vector *this)
{
	if (this == NULL)
		return ;
	if (this->data != NULL)
		free(this->data);
	this->data = NULL;
	free(this);
	this = NULL;
}

void	delete_free(t_vector *this, void (*f)(void *))
{
	if (!this)
		return ;
	if (this->data != NULL)
	{
		while (!is_empty(this))
			f(remove_at(this, this->size - 1));
		free(this->data);
		this->data = NULL;
	}
	free(this);
	this = NULL;
}
