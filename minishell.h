/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:16:23 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/05 17:50:23 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "utility/ft_vector.h"

typedef char	*t_string;
typedef enum	e_type
{
				left = 0,
				right = 1,
				right_append = 2
}				t_type;
typedef struct	s_redir
{
	t_type		type;
	char		*arg;
}				t_redir;
typedef struct	s_cmd
{
	char		*argv[256];
	t_vector	*redirs;
}				t_cmd;

void ft_exit(char *msg, int code);

#endif