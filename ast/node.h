//
// Created by moboustt on 11/4/2021.
//

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../lexer/lexer.h"

enum node_type_e {
    NODE_COMMAND,           /* simple command */
    NODE_ARG,               /* arg name (or simply, a word) */
};

union symval_u {
    char              *str;
};


typedef struct s_node {
    enum   node_type_e type;    /* type of this node */
    enum   e_val_type val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct s_node *first_child; /* first child node */
    struct s_node *next_sibling, *prev_sibling; /*
                                                 * if this is a child node, keep
                                                 * pointers to prev/next siblings
                                                 */
}       t_node;

t_node *new_node(enum node_type_e type);
void set_node_val_str(t_node *node, char *val, TokenType type);
void add_child_node(t_node *parent, t_node *child);

#endif //NODE_H
