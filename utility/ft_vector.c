/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:30:30 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/27 17:22:02 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

/*
** EXIT
*/
void		ft_exit(char *msg, int code)
{
	if (msg)
		perror(msg);
	exit(code);
}

/*
** NEW()
*/
t_vector	*new_vector()
{
	return new_vector_s(10);
}

/*
** NEW(LEN)
*/
t_vector	*new_vector_s(t_size init_len)
{
	t_vector *new_vector;

	if (!(new_vector = (t_vector *)malloc(sizeof(t_vector))))
		ft_exit(ERR_MALLOC, 1);
	if (!(new_vector->data = (void **)malloc(sizeof(void *) * init_len)))
		ft_exit(ERR_MALLOC, 1);
	new_vector->capacity = init_len;
	new_vector->size = 0;
	new_vector->current = 0;
	new_vector->insert = insert;
	new_vector->at = at;
	new_vector->remove_at = remove_at;
	new_vector->clear_free = clear_free;
	new_vector->clear = clear;
	new_vector->contains = contains;
	new_vector->index_of = index_of;
	new_vector->search = search;
	new_vector->sort = sort;
	new_vector->swap = swap;
	new_vector->move_to_first = move_to_first;
	new_vector->move_to_last = move_to_last;
	new_vector->display = display_vector;
	new_vector->data[new_vector->size] = NULL;
	return (new_vector);
}

/*
** NEW(OTHER)
*/
t_vector	*new_vector_from(t_vector *other)
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

/*
** AT(POS)
*/
void		*at(t_vector *this, size_t pos)
{
	if (this == NULL)
		ft_exit("Error\nAccessing items of a NULL Vector!", 1);
	if (pos >= this->size)
		ft_exit("Error\nIndex Out Of Bounds!", 1);
	return (this->data[pos]);
}

/*
** IS_EMPTY()
*/
int			is_empty(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNULL Vector!", 1);
	return (this->size == 0);
}

/*
** INSERT(ITEM)
*/
void		insert(t_vector *this, void *item)
{
	void **old_data;
	size_t new_capacity;
	int i;

	if (this == NULL)
		ft_exit("Error\nInserting in a NULL Vector!", 1);
	if (this->size == this->capacity - 1)
	{
		i = -1;
		new_capacity = this->capacity + this->capacity / 2;
		old_data = (void **)malloc(sizeof(void *) * new_capacity);
		while (++i < this->size)
			old_data[i] = this->data[i];
		free(this->data);
		this->data = old_data;
		this->capacity = new_capacity;
	}
	this->data[this->size++] = item;
	this->data[this->size] = NULL;
	
}

/*
** REMOVE(POS)
*/
void		*remove_at(t_vector *this, t_size pos)
{
	int i;
	void *item;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (is_empty(this))
		return NULL;
	if (pos >= this->size)
		return NULL;
	i = pos;
	item = at(this, pos);
	while (i < this->size)
	{
		if (i + 1 < this->size)
			this->data[i] = this->data[i + 1];
		i++;
	}
	this->size--;
	this->data[this->size] = NULL;
	return (item);
}

/*
** CLEAR()
*/
void		clear(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	this->size = 0;
}

/*
** CLEAR_FRE()
*/
void		clear_free(t_vector *this)
{
	int  i;


	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = this->size;
	while (--i >= 0)
		free(remove_at(this, i));
}

/*
** DELETE()
*/
void		delete(t_vector *this)
{
	if (this == NULL || this->data == NULL)
		ft_exit("Error\nNull Vector!", 1);
	free(this->data);
	free(this);
}

/*
** DELETE_FRE()
*/
void		delete_free(t_vector *this)
{
	int i;

	i = -1;
	if (this == NULL || this->data == NULL)
		ft_exit("Error\nNull Vector!", 1);
	while (++i < this->size)
		free(at(this, i));
	delete(this);
}

/*
** LAST()
*/
void		*last(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(this))
		return (this->data[this->size - 1]);
	return (NULL);
}

/*
** FIRST()
*/
void		*first(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (!is_empty(this))
		return (this->data[0]);
	return (NULL);
}

/*
** CONTAINS(ITEM)
*/
t_bool		contains(t_vector *this, void *item, t_bool (*eql)(void *, void *))
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (eql(this->data[i], item))
			return (true);
	}
	return (false);
}

/*
** INDEX_OF(ITEM)
*/
int			index_of(t_vector *this, void *item, t_bool (*eql)(void *, void *))
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (eql(this->data[i], item))
			return (i);
	}
	return (-1);
}

/*
** INDEX_OF(ITEM)
*/
void		*search(t_vector *this, void *item, t_bool (*eql)(void *, void *))
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (eql(this->data[i], item))
			return (this->data[i]);
	}
	return (NULL);
}

/*
** CAPACITY()
*/
t_size		capacity(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	return (this->capacity);
}

/*
** SWAP(POS, POS)
*/
void		swap(t_vector *this, t_size pos1, t_size pos2)
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

/*
** MOVE_TO_LAST(POS)
*/
void		move_to_last(t_vector *this, t_size pos)
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

/*
** MOVE_TO_FIRST(POS)
*/
void		move_to_first(t_vector *this, t_size pos)
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

/*
** DISPLAY_VECTOR(HOW)
*/
void		display_vector(t_vector *this, char *(*to_string)(void *item))
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

/*
** SORT(HOW)
*/
void		sort(t_vector *this, int (*f)(void *, void *))
{
	int		i;
	int		j;
	int		size;

	i = -1;
	j = -1;
	size = this->size;
	while (++i < this->size)
	{
		while (++j < size - 1)
		{
			if (f(at(this, j), at(this, j + 1)) > 0)
				swap(this, j, j + 1);
		}
		size--;
		j = -1;
	}
}


/*
** CONDIDATES FOR DELETE
*/
void		*remove_item(t_vector *this, void *item)
{
	int i;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	i = -1;
	while (++i < this->size)
	{
		if (this->data[i] == item)
			return (remove_at(this, i));
	}
	return (NULL);
}


void		*previous(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (--this->current >= 0)
		return (this->data[this->current]);
	return (NULL);
}

void		*next(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
	if (this->current < this->size)
		return (this->data[(this->current)++]);
	return (NULL);
}

t_pair		*next_pair(t_vector *this)
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


