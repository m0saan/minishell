//
// Created by moboustt on 11/4/2021.
//

#include "node.h"

/*
 * The new_node() function creates a new node and sets it's type field.
 */

t_node *new_node(enum node_type_e type) {
    t_node *node = malloc(sizeof(t_node));
    if(!node)
        return NULL;
    ft_memset(node, 0, sizeof(t_node));
    if (type == NODE_COMMAND)
        node->val_type = none;
    node->type = type;
    return node;
}

/*
 * The set_node_val_str() function sets a node's value to the given string.
 * It copies the string to a newly allocated memory space,
 * then sets the val_type and val.str fields accordingly.
 */

void set_node_val_str(t_node *node, char *val, TokenType type) {
    node->val_type = type;
    if (!val)
        node->val.str = NULL;
    else {
        size_t l = ft_strlen(val);
        char *tmp = malloc(sizeof (char ) *  l + 1);
        if (!tmp)
            node->val.str = NULL;
        else {
            strcpy(tmp, val);
            node->val.str = tmp;
        }
    }
}

/*
 * The add_child_node() function expands the AST of a simple command
 * by adding a new child node and incrementing the root node's children field.
 */

void add_child_node(t_node *parent, t_node *child) {
    if (!parent || !child)
        return;
    if (!parent->first_child)
        parent->first_child = child;
    else {
        t_node *sibling = parent->first_child;
        while (sibling->next_sibling)
            sibling = sibling->next_sibling;
        sibling->next_sibling = child;
        child->prev_sibling = sibling;
    }
    ++parent->children;
}