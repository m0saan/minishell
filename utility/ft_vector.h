/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:05:53 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/05 18:02:40 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define ERR_MALLOC "Error\nCannot Allocate Memory!"

typedef unsigned long t_size;

typedef enum	e_bool
{
	false = 0,
	true = 1
}				t_bool;

typedef struct	s_vector
{
	void **data;
	t_size capacity;
	t_size size;
	t_size current;
	void (*insert)(struct s_vector *this, void *item);
	void *(*at)(struct s_vector *this, t_size pos);
	void *(*remove_at)(struct s_vector *this, t_size pos);
	void (*clear_free)(struct s_vector *this);
	void (*clear)(struct s_vector *this);
	int (*contains)(struct s_vector *this, void *item);
	int (*index_of)(struct s_vector *this, void *item);
	void (*swap)(struct s_vector *this, t_size pos1, t_size pos2);
	void (*move_to_last)(struct s_vector *this, t_size pos);
	void (*move_to_first)(struct s_vector *this, t_size pos);
	void (*display)(struct s_vector *this, char *(*to_string)(void *item));
}				t_vector;

typedef struct	s_pair
{
	void	*get[2];
}				t_pair;

t_vector *new_vector();
t_vector *new_vector_s(t_size init_len);
t_vector *new_vector_from(t_vector *vector);
void insert(t_vector *vector, void *item);

void *remove_at(t_vector *vector, t_size pos);
void clear(t_vector *vector);
void clear_free(t_vector *this);
void delete (t_vector *vector);
void delete_free(t_vector *this);
void *at(t_vector *vector, t_size pos);
int contains(t_vector *vector, void *item);
int index_of(t_vector *vector, void *item);
int is_empty(t_vector *vector);
void swap(t_vector *vector, t_size pos1, t_size pos2);
void move_to_last(t_vector *vector, t_size pos);
void move_to_first(t_vector *vector, t_size pos);
void display_vector(t_vector *vector, char *(*to_string)(void *item));

void *remove_item(t_vector *vector, void *item);
void *next(t_vector *vector);
void *previous(t_vector *vector);
void *last(t_vector *vector);
void *first(t_vector *vector);
t_pair *next_pair(t_vector *this);
t_size capacity(t_vector *vector);







#endif