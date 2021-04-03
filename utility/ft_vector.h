/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:05:53 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/03 15:21:07 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define ERR_MALLOC "Error\nCannot Allocate Memory!"

typedef unsigned long t_size;

typedef enum e_bool
{
	false = 0,
	true = 1
} t_bool;

typedef struct s_vector
{
	void **data;
	t_size capacity;
	t_size size;
	t_size current;
} t_vector;

t_vector *new_vector();
t_vector *new_vector_s(t_size init_len);
t_vector *new_vector_from(t_vector *vector);
void insert(t_vector *vector, void *item);
void remove_item(t_vector *vector, void *item);
void remove_at(t_vector *vector, t_size pos);
void clear(t_vector *vector);
void delete (t_vector *vector);
void *next(t_vector *vector);
void *previous(t_vector *vector);
void *last(t_vector *vector);
void *first(t_vector *vector);
void *at(t_vector *vector, t_size pos);

int contains(t_vector *vector, void *item);
int index_of(t_vector *vector, void *item);
int is_empty(t_vector *vector);
t_size capacity(t_vector *vector);

void swap(t_vector *vector, t_size pos1, t_size pos2);
void move_to_last(t_vector *vector, t_size pos);
void move_to_first(t_vector *vector, t_size pos);
void display_vector(t_vector *vector, char *(*to_string)(void *item));

#endif