/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:08:08 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:46:28 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_utility.h"
#include "../include/ft_vector.h"

int	index_of(t_vector *this, void *item, t_bool (*eql)(void *, void *))
{
	int	i;

	if (this == NULL)
		exit(1);
	i = -1;
	while (++i < this->size)
	{
		if (eql(this->data[i], item))
			return (i);
	}
	return (-1);
}

void	*search(t_vector *this, void *item, t_bool (*eql)(void *, void *))
{
	int	i;

	if (this == NULL)
		exit(1);
	i = -1;
	while (++i < (int) this->size)
	{
		if (eql(this->data[i], item))
			return (this->data[i]);
	}
	return (NULL);
}

t_size	capacity(t_vector *this)
{
	if (this == NULL)
		exit(1);
	return (this->capacity);
}

void	swap(t_vector *this, t_size pos1, t_size pos2)
{
	void	*item;

	if (this == NULL)
		exit(1);
	if (pos1 >= this->size || pos2 >= this->size || pos1 == pos2)
		return ;
	item = this->data[pos1];
	this->data[pos1] = this->data[pos2];
	this->data[pos2] = item;
}

void	sort(t_vector *this, int (*f)(void *, void *))
{
	int	i;
	int	j;
	int	size;

	i = -1;
	j = -1;
	size = (int) this->size;
	while (++i < (int) this->size)
	{
		while (++j < size - 1)
			if (f(at(this, j), at(this, j + 1)) > 0)
				swap(this, j, j + 1);
		size--;
		j = -1;
	}
}
