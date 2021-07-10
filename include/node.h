/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:54:17 by moboustt          #+#    #+#             */
/*   Updated: 2021/07/10 20:53:56 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include <stdlib.h>
# include "lexer.h"

enum e_node_type {
	NODE_COMMAND,
	NODE_ARG,
};

typedef struct s_node {
	enum e_node_type	type;
	enum e_val_type		val_type;
	char				*val;
	int					children;
	struct s_node		*first_child;
	struct s_node		*next_sibling;
	struct s_node		*prev_sibling;
}				t_node;

t_node	*new_node(enum e_node_type type);
void	set_node_val_str(t_node *node, char *val, t_token_t type);
void	add_child_node(t_node *parent, t_node *child);

#endif
