#include "minishell.h"

const char *prompt = "minishell-0.1$ ";

size_t read_line(char *line) {
	ft_memset(line, 0, 1024);
	size_t n = read(0, line, 1024);
	if(n)
		line[n - 1] = 0;
	return (n);
}

t_cmd *create_cmd() {
	t_cmd *command;
	command = malloc(sizeof(t_cmd));
	ft_memset(command, 0, sizeof(t_cmd));
	command->redirs = new_vector();
	return (command);
}

t_vector *fill_out_vector_with_commands(t_node *ast_node) {
	t_node *child;
	t_vector *vector = new_vector();
	t_cmd *tmp_cmd;

	child = ast_node->first_child;
	tmp_cmd = create_cmd();
	while(child) {
		if(child->val_type == right) {
			struct s_redir *tmp = create_redir(right, child->next_sibling->val.str);
			child = child->next_sibling;
			insert(tmp_cmd->redirs, tmp);
		} else if(child->val_type == left) {
			insert(tmp_cmd->redirs, create_redir(left, child->next_sibling->val.str));
			child = child->next_sibling;
		} else if(child->val_type == right_append) {
			insert(tmp_cmd->redirs, create_redir(right_append, child->next_sibling->val.str));
			child = child->next_sibling;
		}
		else if(child->val_type == heredoc) {
			insert(tmp_cmd->redirs, create_redir(heredoc, child->next_sibling->val.str));
			child = child->next_sibling;
		}
		else if(child->val.str[0] == '$' && child->val_type == env_var) {
			if(child->val.str != NULL) {
				char *tmp = handle_env_variables(child->val.str, 0, 0);
				if(tmp != NULL)
					fill_out_env_command(tmp_cmd, tmp);
			} else
				tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
		} else if(child->val_type == _pipe) {
			insert(vector, tmp_cmd);
			tmp_cmd = create_cmd();
		} else
			tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
		child = child->next_sibling;
	}
	insert(vector, tmp_cmd);
	return (vector);
}

void fill_out_env_command(t_cmd *tmp_cmd, const char *tmp) {
	char **splited_env_value;
	int i;

	splited_env_value = ft_split(tmp, ' ');
	i = -1;
	while(splited_env_value[++i] != 0)
		tmp_cmd->argv[tmp_cmd->count++] = splited_env_value[i];
}

t_error *check_first_token(t_parser *p) {
	const enum e_val_type types[] = {illegal, end_of, semicolon, _pipe, right, left, right_append};
	t_error *error;
	int i;
	error = malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	i = -1;
	while(++i < 7) {
		if((p->cur_token->type == types[i] && p->peek_token->type == end_of) || \
        p->cur_token->type == end_of)
			set_error(error, ERR1);
	}
	return (error);
}

void parse_and_execute(t_lexer *lexer) {
	t_cmd *cmd;
	t_node *ast_node;
	t_parser *p;
	t_error *err;

	cmd = malloc(sizeof(t_cmd));
	p = new_parser(lexer);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->redirs = new_vector();
	err = check_first_token(p);
	if(err->is_error) {
		printf("%s '%s'\n", err->error_msg, p->peek_token->literal);
		return;
	}
	ast_node = parse_command(ast_node, p);
	if(ast_node == NULL)
		return;
	run_cmds((t_vector *) fill_out_vector_with_commands(ast_node));
}

/*
t_bool	check_semicolon_errors(const char *line)
{
	t_parser *p;

	p = new_parser(new_lexer(line, (int) ft_strlen(line)));
	while (p->cur_token->type != end_of)
	{
		next_token_p(p);
		if (p->cur_token->type == semicolon && p->peek_token->type == semicolon)
		{
			free(p);
			return (true);
		}
	}
	free(p);
	return (false);
}
*/

void signal_handler_parent(int sig) {
	if(sig == SIGQUIT && g_is_forked)
		dprintf(1, "Quit: 3");
	if(!(sig == SIGQUIT && !g_is_forked))
		dprintf(1, "\n");
	if(sig == SIGINT && !g_is_forked)
		dprintf(1, "%s", prompt);
}

void signal_handler(int sig) {
	// if (sig == SIGQUIT)
	// 	dprintf(2, "^\\\n");
	// else if (sig == SIGINT)
	// 	dprintf(2, "^C\n");
}

#if (1)

/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char * rl_gets ()
{
	/* If the buffer has already been allocated, return the memory
	   to the free pool. */
	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}

	/* Get a line from the user. */
	line_read = readline (prompt);

	/* If the line has any text in it, save it on the history. */
	if (line_read && *line_read)
		add_history (line_read);
	//rl_redisplay();
	return (line_read);
}

int main(int ac, char **av, char **env) {
	char *line;

	g_is_forked = false;
	fill_envp(env);
	signal(SIGQUIT, signal_handler_parent);
	signal(SIGINT, signal_handler_parent);
	while(true)
	{
		// write(1, prompt, ft_strlen(prompt));
		//line = malloc(1024 * sizeof(char));
		//size_t n = read_line(line);
		line = rl_gets();
//		if(strcmp(line, "exit") == 0) {
//			dprintf(2, "shell is exiting...\n");
//			free(line);
//			break;
//		}
		if (line && line[0] == '\0')
			continue;
		t_lexer *lexer = new_lexer(line, (int) ft_strlen(line));
		parse_and_execute(lexer);
	}
	return (EXIT_SUCCESS);
}

#endif 
