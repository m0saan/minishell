//
// Created by moboustt on 4/4/2021.
//

#include "../minishell.h"

const char* commands[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

TokenType lookup_type(char *ident) {
    for (int i = 0; i < 7; ++i) {
        if (strcmp(ident, commands[i]) == 0)
            return command;
    }
    return arg;
}

t_token *new_token(TokenType token_type, char ch, t_token *token) {
    char *tmp = malloc(2);
    token->Type = token_type;
    tmp[0] = ch;
    tmp[1] = 0;
    token->literal = tmp;
    return token;
}

t_token *new_token_from_char(TokenType token_type, char *ch, t_token *token) {
    token->Type = token_type;
    token->literal = ch;
    return token;
}