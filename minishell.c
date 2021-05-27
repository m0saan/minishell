/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:21:54 by ehakam            #+#    #+#             */
/*   Updated: 2021/05/27 18:36:54 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *prompt = "minishell-0.1$ ";

/*
 * Here the shell runs in a loop,
 * which we know as the Read-Eval-Print-Loop, or REPL.
 */

size_t readline(char *line) {
    size_t n = read(0, line, 1024);
    line[n - 1] = 0;
    return n;
}

void str__(t_token *tok) {
    printf("TokenType: [%s], Literal: [%s]\n", getTypeName(tok->Type), tok->literal);
}

const char *getTypeName(enum e_val_type type) {
    switch (type) {
        case left:
            return "Left Redirection";
        case right:
            return "Right Redirection";
        case right_append:
            return "Right Append";
        case _pipe:
            return "PIPE";
        case env_var:
            return "Environment Variable";
        case none:
            return "None";
        case VAL_STR:
            return "Value String";
        default:
            return "No such type";
    }
}

char * Print(struct s_cmd *this) {

    if (this == NULL)
        ft_exit("Error\nNull CMD!", 1);

    //printf("REDIRECT:\n");
    //for (size_t i = 0; i < this->redirs->size; ++i) {
    //    t_redir *tRedir = this->redirs->at(this->redirs, i);
    //    printf("{ type: %s -- arg: %s}\n", getTypeName(tRedir->type), tRedir->arg);
    //}

    //printf("--------------------------------------------\n");
    char *line = malloc(1024);
    bzero(line, 1024);
    //printf("ARGS:\n");
    for (int i = 0; this->argv[i] != 0; i++) {
        strcat(line, this->argv[i]);
        if (this->argv[i+1] != 0)
            strcat(line, " ");
       // printf("ARGS%d |%s|\n", i+1, this->argv[i]);
    }
    return line;
}

t_cmd *create_cmd() {
    t_cmd *command = malloc(sizeof(t_cmd));
    ft_memset(command, 0, sizeof(t_cmd));
    command->redirs = new_vector();
    return command;
}

t_vector *fill_out_vector_with_commands(t_node *ast_node) {
    t_node *child;
    t_vector *vector = new_vector();
    t_vector *tmp_vector = NULL;
    t_cmd *tmp_cmd = NULL;


    while (ast_node) {
        child = ast_node->first_child;
        tmp_vector = new_vector();
        tmp_cmd = create_cmd();
        while (child) {
            if (child->val_type == right) {
                struct s_redir *tmp = create_redir(right, child->next_sibling->val.str);
                child = child->next_sibling;
                insert(tmp_cmd->redirs, tmp);
            } else if (child->val_type == left) {
                insert(tmp_cmd->redirs, create_redir(left, child->next_sibling->val.str));
                child = child->next_sibling;
            } else if (child->val_type == right_append) {
                insert(tmp_cmd->redirs, create_redir(right_append, child->next_sibling->val.str));
                child = child->next_sibling;
            } else if (child->val.str[0] == '$' && child->val_type == env_var) {
                if (child->val.str != NULL) {
                    char *tmp =  handle_env_variables(child->val.str);
                    if (tmp != NULL)
                        tmp_cmd->argv[tmp_cmd->count++] = tmp;
                }
                else
                    tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
            } else if (child->val_type == _pipe) {
                insert(tmp_vector, tmp_cmd);
                tmp_cmd = create_cmd();
            } else
                tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
            child = child->next_sibling;
        }
        insert(tmp_vector, tmp_cmd);
        insert(vector, tmp_vector);
        ast_node = ast_node->next_sibling;
    }
    return vector;
}

t_error *check_first_token(t_parser *p) {
    t_error *error = malloc(sizeof(t_error));
    ft_memset(error, 0, sizeof (t_error));
    enum e_val_type types[] = {illegal, end_of, semicolon, _pipe, right, left, right_append};
    for (int i = 0; i < 7; ++i) {
        if ((p->cur_token->Type == types[i] && p->peek_token->Type == end_of) || p->peek_token->Type == end_of)
            set_error(error, ERR1);
    }
    return error;
}

void parse_and_execute(t_lexer *lexer) {
    t_cmd *cmd;
    t_node *ast_node = NULL; //  = malloc(sizeof (t_node));
    t_parser *p = new_parser(lexer);
    cmd = malloc(sizeof(t_cmd));
    ft_memset(cmd, 0, sizeof(t_cmd));
    cmd->redirs = new_vector();

    // t_error *err = check_first_token(p);

    // if (err->is_error) {
    //     printf("%s '%s'\n", err->error_msg, p->peek_token->literal);
    //     return;
    // }

    ast_node = parse_command(ast_node, p);
    if (ast_node == NULL)
        return;
    t_vector *vector = fill_out_vector_with_commands(ast_node);
    // stream = Print(at(at(vector, 0), 0));
    //printf("%s\n", stream);
	run_cmds((t_vector *)at(vector, 0));
    // Print(at(at(vector, 0), 1));
    // Print(at(at(vector, 0), 2));
    // Print(at(at(vector, 1), 0));
    // delete_free(vector);
    // printf("%s type", pSNode->val.str);
    // t_vector *v = at(vector, 0);
    // display_vector(v, to_string);
    // display_vector(v, 1, to_string);
    // execute(v);
    // free(pSNode)
}

#if (1)

int main(int ac, char **av, char **env)
{
	fill_envp(env);
    while (true) {
        write(1, prompt, ft_strlen(prompt));
        char *line = malloc(1024 * sizeof(char));
        size_t n = readline(line);
        if (!n || line[0] == '\0' || strcmp(line, "\n") == 0) {
            free(line);
            continue;
        }

        if (strcmp(line, "exit") == 0) {
            printf("shell is exiting...\n");
            free(line);
            break;
        }

        t_lexer *lexer = new_lexer(line, (int) n);
        // if (check_entered_command(line)) {
        //     printf("%s\n", "syntax error in quotes.");
        //     free(line);
        //     continue;
        // }
        parse_and_execute(lexer);
        if (errno == ENODATA)
            ft_exit("TTTT", errno);

        free(line);
    }
    return (EXIT_SUCCESS);
}

#endif 
