/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:58:44 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/27 16:52:56 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
#define FT_ENV_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_types.h"
#include "ft_vector.h"

typedef struct	s_var
{
	char	*raw;
	char	*key;
	char	*value;
}				t_var;

t_var	*new_var();
t_var	*new_var_v(char *key, char *value, char *raw);
t_var	*split_key_value(struct s_var *var, char *var_str);
t_var	*split_key_value_v(char *var_str);
t_bool	equals(void *item1, void *item2);
t_bool	equals_key(void *item1, void *item2);
t_bool	check_key(t_var *var);
int		set_var(t_vector *env, char *var_str);
char	*get_var(t_vector *env, char *key);
t_var	*get_var_2(t_vector *env, char *key);

#endif