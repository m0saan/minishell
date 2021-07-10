/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 19:50:44 by moboustt          #+#    #+#             */
/*   Updated: 2021/07/10 20:26:26 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/node.h"

t_node	*new_node(enum e_node_type type)
{
	t_node	*node;

	node = ft_malloc(sizeof(t_node));
	ft_memset(node, 0, sizeof(t_node));
	if (type == NODE_COMMAND)
		node->val_type = NONE;
	node->type = type;
	return (node);
}

void	set_node_val_str(t_node *node, char *val, t_token_t type)
{
	node->val_type = type;
	if (!val)
	{
		node->val = NULL;
		free(val);
	}
	else
		node->val = val;
}

void	add_child_node(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent || !child)
		return ;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	++parent->children;
}
