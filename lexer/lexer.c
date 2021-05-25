//
// Created by moboustt on 4/4/2021.
//

#include "../minishell.h"

void read_and_parse_double_quoted(t_lexer *l, char *s, int *index, t_error *err);

char *parse_quoted(t_lexer *l, char quote);

t_bool is_quote(const t_lexer *l);

t_lexer *new_lexer(const char *line, int cmd_length) {
    t_lexer *lexer = malloc(sizeof(t_lexer));
    *lexer = (t_lexer) {.input = (char *) line, .len = cmd_length, .readPosition = 0, .position = 0, .ch = ' ', .is_error = false};
    next_char(lexer);
    return lexer;
}

void skip_white_spaces(t_lexer *l) {
    if (!l || !l->input) {
        errno = ENODATA;
        return;
    }
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n') {
        next_char(l);
    }
}

char peek_char(t_lexer *l) {
    if (l->readPosition >= l->len)
        return 0;
    else
        return l->input[l->readPosition];
}

void next_char(t_lexer *lexer) {
    if (!lexer || !lexer->input)
        errno = ENODATA; //  ENODATA : set errno to 61 -> No data available
    if (lexer->readPosition >= lexer->len)
        lexer->ch = 0;
    else
        lexer->ch = lexer->input[lexer->readPosition];
    lexer->position = lexer->readPosition;
    ++lexer->readPosition;
}

enum e_bool has_char(char c) {
    char *buff = "?=._-/\\$";
    for (int i = 0; buff[i] != 0; ++i)
        if (buff[i] == c) return true;
    return false;
}

enum e_bool is_letter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9') || has_char(ch);
}

int *has_next_quote(t_lexer *l, char quote) {
    int las_quote_index = 0;
    int n_of_quotes = 0;
    int *res = malloc(2 * sizeof(int));
    int i = l->position;
    while (i < l->len) {
        if (l->input[i] == quote) {
            n_of_quotes++;
            las_quote_index = i;
        }
        i++;
    }
    if (n_of_quotes == 0 && las_quote_index == 0)
        return NULL;
    res[0] = n_of_quotes;
    res[1] = (las_quote_index);
    return res;
}

t_token *next_token(t_lexer *l) {
    t_token *tok = malloc(sizeof(t_token));
    tok->lexer = l;
    tok->str__ = str__;
    skip_white_spaces(l);
    switch (l->ch) {
        case '~':
            tok = new_token(tilde, l->ch, tok);
            break;
        case ';':
            tok = new_token(semicolon, l->ch, tok);
            break;
        case '<':
            tok = new_token(left, l->ch, tok);
            break;
        case '>':
            if (peek_char(l) == '>') {
                next_char(l);
                tok = new_token(right_append, 'r', tok);
                break;
            } else {
                tok = new_token(right, l->ch, tok);
                break;
            }
        case '|':
            tok = new_token(_pipe, l->ch, tok);
            break;
        case '\'':
            // tok = new_token(single_quote, l->ch, tok);
            tok->literal = parse_quoted(l, l->ch);
            if (!tok->literal)
                tok->Type = illegal;
            else
                tok->Type = arg;
            break;
        case '\"':
            // tok = new_token(DOUBLE_QUOTE, l->ch, tok);
            tok->literal = parse_quoted(l, l->ch);
            if (!tok->literal)
                tok->Type = illegal;
            else
                tok->Type = arg;
            break;
        case '\\':
            tok->literal = read_identifier(l);
            return tok;
        case '$':
            tok->Type = env_var;
            tok->literal = read_identifier(l);
            return tok;
        case 0:
            tok->literal = "newline";
            tok->Type = end_of;
            return tok;
        default:
            if (is_letter(l->ch)) {
                tok->literal = read_identifier(l);
                if (l->ch == '"' || l->ch == '\'') {
                    char *tmp = parse_quoted(l, l->ch);
                    if (tmp == NULL) {
                        tok->Type = illegal;
                        return tok;
                    }
                    tok->literal = strcat(tok->literal, tmp);
                }
                tok->Type = lookup_type(tok->literal);
                return tok;
            } else {
                tok = new_token(illegal, l->ch, tok);
                errno = EPERM;
                return tok;
            }
    }
    next_char(l);
    return tok;
}

void slice_str(const char *str, char *buffer, size_t start, size_t end) {
    size_t j = 0;
    for (size_t i = start; i < end; ++i) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}


char *read_identifier(t_lexer *l) {
    char *s = malloc(100);
    ft_bzero(s, 100);
    int i = 0;
    while (is_letter(l->ch)) {
        if (l->ch == '\\')
            next_char(l);
        s[i++] = l->ch;
        next_char(l);
    }
    return s;
}

void read_single_quoted(t_lexer *l, char quote, char *s, int *index, t_error *err) {
    next_char(l);
    if (!has_closing_quote(l->input, l->position, '\'')) {
        set_error(err, "syntax error in quotes.");
        return;
    }
    while (l->ch != quote) {
        if (*index > l->len) {
            l->is_error = true;
            return;
        }
        s[(*index)++] = l->ch;
        next_char(l);
//        if (l->ch == '\'' && l->input[l->position - 1] == '\\') {
//            s[(*index)++] = l->ch;
//            next_char(l);
//       }
    }
    next_char(l);
}

size_t get_env_var_last_index(t_lexer *l) {
    int counter;

    counter = l->position;
    while (ft_isalnum(l->ch))
        next_char(l);
    return counter;
}

char *get_env_value(t_lexer *l) {
    char *env_name = malloc(100);
    ft_bzero(env_name, 100);
    size_t start = get_env_var_last_index(l);
    slice_str(l->input, env_name, start, l->position);
    char *env_value = get_var(g_envp,env_name);
    if (env_value == NULL)
        return NULL;
    return env_value;
}

char *parse_quoted(t_lexer *l, char quote) {
    char *s = malloc(1024);
    t_error *err = create_error();
    ft_bzero(s, 1024);
    int i = 0;
    int s_index = 0;
    int *infos = has_next_quote(l, quote);
    while (i++ < infos[1] && l->ch != 0) {
        if (l->ch == '\\') {
            next_char(l);
            s[s_index++] = l->ch;
            next_char(l);
            i += 2;
            continue;
        }
        if (l->ch == '"') {
            int pos = l->position;
            read_and_parse_double_quoted(l, s, &s_index, err);
            if (err->is_error)
                return NULL;
            i += (l->position - pos);
        } else if (l->ch == '\'') {
            int pos = l->position;
            read_single_quoted(l, l->ch, s, &s_index, err);
            if (err->is_error)
                return NULL;
            i += (l->position - pos);
        } else if (ft_isalnum(l->ch)) {
            int pos = l->position;
            s = strcat(s, read_identifier(l));
            i += (l->position - pos);
            s_index += (l->position - pos);
        }
        if (is_quote(l))
            infos = has_next_quote(l, l->ch);
        if (l->ch == ' ')
            return s;
        if (l->is_error)
            return NULL;
    }
    return s;
}

t_bool is_quote(const t_lexer *l) { return l->ch == '\'' || l->ch == '"'; }

t_bool has_closing_quote(const char *line, int i, char quote) {
    while (line[i]) {
        if (line[i] == quote && line[i] != '\\')
            return true;
        i++;
    }
    return false;
}

void read_and_parse_double_quoted(t_lexer *l, char *s, int *index, t_error *err) {
    char *env_name;
    next_char(l);
    char const to_be_escaped[] = {'$', '"', '\\'};
    if (!has_closing_quote(l->input, l->position, '"')) {
        set_error(err, "syntax error in quotes.");
        return;
    }
    while (l->ch != '"') {
        if (l->ch == '\\' && ft_strchr(to_be_escaped, peek_char(l))) {
            next_char(l);
            s[*index] = l->ch;
            (*index) += 1;
            next_char(l);
            continue;
        }
        if (l->ch == '$' && ft_isalnum(l->input[l->readPosition])) {
            next_char(l);
            if (ft_isdigit(l->ch)) {
                next_char(l);
                continue;
            }
            env_name = get_env_value(l);
            if (env_name == NULL)
                continue;
            s = strcat(s, env_name);
            (*index) += (int) ft_strlen(env_name);
            continue;
        }
        s[(*index)++] = l->ch;
        next_char(l);
    }
    next_char(l);
}

int get_env_var_end(t_string str) {
    int counter;

    counter = 0;
    while (ft_isalnum(str[counter]))
        counter++;
    return counter;
}

char *handle_env_variables(t_string str) {
    int i = 0;
    int k = 0;
    char env_name[100] = {};
    char *tmp = malloc(1204 * sizeof(char));
    ft_memset(env_name, 0, sizeof(env_name) / sizeof(env_name[0]));
    ft_memset(tmp, 0, 256);
    while (str[i] != 0 && i < (int) ft_strlen(str)) {
        if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i+1] == '?')) {
            i++;
            size_t end = get_env_var_end(&str[i]) + i;
            slice_str(str, env_name, i, end);
            char *env_value = get_var(g_envp,env_name);
            if (env_value == NULL) {
                i += (int) ft_strlen(env_name);
                ft_memset(env_name, 0, 100);
                continue;
            }
            tmp = strcat(tmp, env_value);
            i += (int) ft_strlen(env_name);
            k += (int) ft_strlen(env_value);
            continue;
        }
        tmp[k++] = str[i];
        i++;
    }
    return tmp;
}