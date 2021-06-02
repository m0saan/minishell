//
// Created by moboustt on 18/4/2021.
//

#ifndef MINISHELL_LEXER_H
#define MINISHELL_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include "../utility/ft_types.h"

typedef enum e_val_type {
    none = -2,
    VAL_STR = -1, /* str (char pointer) */
    left = 0,
    right = 1,
    right_append = 2,
    _pipe = 3,
    env_var = 4,
    command = 5,
    arg = 6,
    illegal = 7,
    end_of,
    semicolon,
    single_quote,
    dollar_sign,
    tilde,
}    t_type;

typedef enum e_val_type TokenType;

typedef struct  s_lexer {
    char *input;
    int position; // current position in input (points to current char)
    int readPosition;  // current reading position in input (after current char)
    char ch; // current char under examination
    int len; // the length of the input.

    t_bool is_error;
}               t_lexer;

typedef struct  s_token  {
    TokenType Type;
    char *literal;
    t_lexer *lexer;
    void (*str__)(struct s_token *);
}               t_token;

t_bool has_closing_quote(const char *line, int i, char quote);
char *get_env_value(t_lexer *l);

#endif //MINISHELL_LEXER_H
