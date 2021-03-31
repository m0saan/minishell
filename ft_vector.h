/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:05:53 by ehakam            #+#    #+#             */
/*   Updated: 2021/03/31 18:13:09 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <unistd.h>

typedef struct s_vector
{
	void **data;
	size_t length;
	size_t size;
	int is_empty;
}				t_vector;

t_vector *new_vector();
t_vector *new_vector_s(size_t length);




#endif