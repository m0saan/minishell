/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:16:23 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/01 15:19:33 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

typedef enum e_types
{
	tstdin = 0,
	tstdout = 1
}			t_type;

typedef struct s_redirect
{
	t_type type;
	char *fname;
} s_redirect;

typedef struct s_cmd {
	char *cmd;
	char *argv[512];
}	t_cmd;

#endif