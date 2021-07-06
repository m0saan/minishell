/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:05:57 by ehakam            #+#    #+#             */
/*   Updated: 2021/07/04 20:41:56 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

typedef char			*t_string;
typedef unsigned long	t_size;
typedef enum			e_bool
{
	false = 0,
	true = 1
}	t_bool;
typedef enum e_val_type
{
	NONE = -2,
	LEFT = 0,
	RIGHT,
	RIGHT_APPEND,
	PIPE,
	ENV_VAR,
	COMMAND,
	ARG,
	ILLEGAL,
	HEREDOC,
	END_O_F,
	SEMICOLON,
	TILDE,
	EXIT_STATUS,
	NEW_LINE,
}			t_type;
typedef enum e_val_type	t_token_type;

#endif