/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:58:44 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/25 17:22:26 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
#define FT_ENV_H

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_types.h"

typedef struct	s_var
{
	char	*key;
	char	*value;
}				t_var;

t_var	*new_var();
t_var	*new_var_v(char *key, char *value);
t_var	*split_key_value(struct s_var *var, char *var_str);
t_var	*split_key_value_v(char *var_str);
t_bool	equals(void *item1, void *item2);


#endif