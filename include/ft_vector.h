/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:05:53 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 18:38:55 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include "ft_types.h"
# include "error.h"
# include "global_utils.h"

typedef struct s_vector
{
	void	**data;
	t_size	capacity;
	t_size	size;
}			t_vector;

t_vector	*new_vector(void);
t_vector	*new_vector_s(t_size init_len);
t_vector	*new_vector_from(t_vector *vector);
void		insert(t_vector *vector, void *item);
void		*remove_at(t_vector *vector, t_size pos);
void		delete (t_vector *vector);
void		*at(t_vector *vector, t_size pos);
t_bool		contains(t_vector *this, void *item, t_bool (*eql)(void *, void *));
void		sort(t_vector *this, int (*f)(void *, void *));
int			index_of(t_vector *vector, void *item,
				t_bool (*eql)(void *, void *));
void		*search(t_vector *vector, void *item,
				t_bool (*eql)(void *, void *));
int			is_empty(t_vector *vector);
void		swap(t_vector *vector, t_size pos1, t_size pos2);

#endif