#include "ft_vector.h"

int	is_empty(t_vector *this)
{
	if (this == NULL)
		ft_exit("Error\nNULL Vector!", 1);
	return (this->size == 0);
}

void	insert(t_vector *this, void *item)
{
	void	**old_data;
	size_t	new_capacity;
	int		i;

	if (this == NULL)
		ft_exit("Error\nInserting in a NULL Vector!", 1);
	if (this->size == this->capacity - 1)
	{
		i = -1;
		new_capacity = this->capacity + this->capacity / 2;
		old_data = (void **) malloc(sizeof(void *) * new_capacity);
		while (++i < this->size)
			old_data[i] = this->data[i];
		free(this->data);
		this->data = old_data;
		this->capacity = new_capacity;
	}
	this->data[this->size++] = item;
	this->data[this->size] = NULL;
}

void	*remove_at(t_vector *this, t_size pos)
{
	int		i;
	void	*item;

	if (this == NULL)
		ft_exit("Error\nNull Vector!", 1);
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
	if (this == NULL || this->data == NULL)
		ft_exit("Error\nNull Vector!", 1);
	free(this->data);
	free(this);
}
