/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:16:23 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/03 15:02:40 by ehakam           ###   ########.fr       */
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
#include "utility/ft_vector.h"

typedef char *t_string;
typedef enum e_redirtype
{
	left = 0,
	right = 1
} t_redirtype;
typedef struct s_redir
{
	t_redirtype type;
	char *arg;
}			t_redir;
typedef struct s_command
{
	char *argv[256];
	t_vector *redirs;
} t_command;

void ft_exit(char *msg, int code);

#endif