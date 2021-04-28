/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:16:23 by ehakam            #+#    #+#             */
/*   Updated: 2021/04/25 17:11:01 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <wait.h>
# include "utility/ft_vector.h"
# include "utility/ft_types.h"
# include "utility/ft_env.h"

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

t_vector	*g_envp;

void ft_exit(char *msg, int code);

#endif