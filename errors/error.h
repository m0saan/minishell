//
// Created by moboustt on 4/5/2021.
//

#ifndef MINISHELL_ERROR_H
#define MINISHELL_ERROR_H

#include <stdlib.h>
#include "../libft/libft.h"
#include "../utility/ft_types.h"

#define ERR1 "syntax error near unexpected token"

typedef struct s_error {
    t_bool is_error;
    char *error_msg;
}               t_error;

void set_error(t_error *error, char *msg);
t_bool         check_entered_command(const char *line);
t_error *create_error();

#endif //MINISHELL_ERROR_H
