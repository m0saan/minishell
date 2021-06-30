#include "minishell.h"

t_cmd *create_cmd() {
	t_cmd *command;
	command = malloc(sizeof(t_cmd));
	ft_memset(command, 0, sizeof(t_cmd));
	command->redirs = new_vector();
	return (command);
}

void parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd);

t_node *init_and_fill_redirs(t_node *child, t_cmd *tmp_cmd, t_type type);

t_bool is_redir(const t_node *child);

t_node *handle_all_redirs(t_node *child, t_cmd *tmp_cmd);

t_vector*	fill_out_vector_with_commands(t_node *ast_node)
{
	t_node		*child;
	t_vector	*vector;
	t_cmd		*tmp_cmd;

	vector = new_vector();
	child = ast_node->first_child;
	tmp_cmd = create_cmd();
	while(child)
	{
		if(is_redir(child))
			child = handle_all_redirs(child, tmp_cmd);
		else if(child->val_type == PIPE)
		{
			insert(vector, tmp_cmd);
			tmp_cmd = create_cmd();
		}
		else
			tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
		child = child->next_sibling;
	}
	insert(vector, tmp_cmd);
	return (vector);
}

t_node *handle_all_redirs(t_node *child, t_cmd *tmp_cmd)
{
	if (child->val_type == RIGHT)
	child = init_and_fill_redirs(child, tmp_cmd, RIGHT);
	else if(child->val_type == LEFT)
		child = init_and_fill_redirs(child, tmp_cmd, LEFT);
	else if(child->val_type == RIGHT_APPEND)
		child = init_and_fill_redirs(child, tmp_cmd, RIGHT_APPEND);
	else if(child->val_type == HEREDOC)
		child = init_and_fill_redirs(child, tmp_cmd, HEREDOC);
	else if(child->val.str[0] == '$' && child->val_type == ENV_VAR)
		parse_env_vars_not_in_quotes(child, tmp_cmd);
	return child;
}

t_bool is_redir(const t_node *child)
{
	return (child->val_type == RIGHT || child->val_type == LEFT ||
			child->val_type == RIGHT_APPEND || child->val_type == HEREDOC);
}

t_node *init_and_fill_redirs(t_node *child, t_cmd *tmp_cmd, t_type type)
{
	struct s_redir *tmp = create_redir(type, child->next_sibling->val.str);
	child = child->next_sibling;
	insert(tmp_cmd->redirs, tmp);
	return child;
}

void parse_env_vars_not_in_quotes(t_node *child, t_cmd *tmp_cmd)
{
	if(child->val.str != NULL)
	{
		char *tmp = handle_env_variables(child->val.str, -1, 0);
		if(tmp != NULL)
			fill_out_env_command(tmp_cmd, tmp);
	}
	else
		tmp_cmd->argv[tmp_cmd->count++] = child->val.str;
}

void fill_out_env_command(t_cmd *tmp_cmd, const char *tmp)
{
	char **splited_env_value;
	int i;

	splited_env_value = ft_split(tmp, ' ');
	i = -1;
	while(splited_env_value[++i] != 0)
		tmp_cmd->argv[tmp_cmd->count++] = splited_env_value[i];
}

t_error *check_first_token(t_parser *p)
{
	const enum e_val_type types[] = {ILLEGAL, END_O_F, SEMICOLON, PIPE, RIGHT, LEFT, RIGHT_APPEND};
	t_error *error;
	int i;
	error = malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	i = -1;
	while(++i < 7) {
		if((p->cur_token->type == types[i] && p->peek_token->type == END_O_F) || \
        p->cur_token->type == END_O_F)
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
	if(err->is_error)
	{
		printf("%s '%s'\n", err->error_msg, p->peek_token->literal);
		return;
	}
	ast_node = parse_command(ast_node, p);
	if(ast_node == NULL)
		return;
	run_cmds((t_vector *) fill_out_vector_with_commands(ast_node));
	free(p);
}

void signal_handler_parent(int sig) {
	const char	*prompt = "minishell-0.1$ ";
	if(sig == SIGQUIT && g_is_forked)
		dprintf(1, "Quit: 3");
	if(!(sig == SIGQUIT && !g_is_forked))
		dprintf(1, "\n");
	if(sig == SIGINT && !g_is_forked)
		dprintf(1, "%s", prompt);
}


#if (1)

static char *line_read = (char *)NULL;

char*	get_line()
{
	const char	*prompt = "minishell-0.1$ ";

	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
	}
	rl_on_new_line();
	line_read = readline (prompt);

	/* If the line has any text in it, save it on the history. */
	if (line_read && *line_read)
		add_history (line_read);
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
		line = get_line();
		if (line && line[0] == '\0')
			continue;
		t_lexer *lexer = new_lexer(line, (int) ft_strlen(line));
		parse_and_execute(lexer);
		free(lexer);
	}
}

#endif