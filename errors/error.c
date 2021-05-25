//
// Created by moboustt on 4/5/2021.
//

#include "error.h"


t_error *create_error() {
    t_error *error = malloc(sizeof(t_error));
    ft_memset(error, 0, sizeof(t_error));
    return error;
}

void set_error(t_error *error, char *msg){
    error->is_error = true;
    error->error_msg = msg;
}

t_bool         check_entered_command(const char *line){
    int i;
    int count_single_quotes;
    int count_double_quotes;

    i = 0;
    count_single_quotes = 0;
    count_double_quotes = 0;
    while (line[i] != 0) {
        if (line[i] == '\'') ++count_single_quotes;
        else if (line[i] == '"') ++count_double_quotes;
        i++;
    }
    if (count_single_quotes%2 != 0 || count_double_quotes%2 != 0)
        return true;
    return false;
}