/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:25:17 by ehakam            #+#    #+#             */
/*   Updated: 2021/06/30 20:26:20 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility/ft_utility.h"
#include "minishell.h"

t_bool	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

t_bool	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

char	*strjoin_s(char *s, char *s2, t_bool free_)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	if (s2)
		i += ft_strlen(s2);
	str = (char *)malloc(i + 1);
	i = 0;
	j = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	while (s2 && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	if (free_)
		free(s);
	return (str);
}

char	*strjoin_c(char *s, char c, t_bool free_)
{
	int		i;
	char	*str;

	i = 0;
	if (s)
		i += ft_strlen(s);
	str = (char *)malloc(i + 2);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		++i;
	}
	str[i] = c;
	str[++i] = '\0';
	if (free_)
		free(s);
	return (str);
}

int		get_next_line(char **line)
{
	char	*buffer;
	int		ret;

	buffer = (char *)malloc(2);
	*line = (char *)malloc(1);
	*line[0] = '\0';
	ret = 1;
	while (ret)
	{
		ret = read(0, buffer, 1);
		if (ret)
		{
			if (buffer[0] == '\n' || ret == EOF)
				break ;
			*line = strjoin_c(*line, buffer[0], true);
		}
	}
	free(buffer);
	return (ret);
}

int		handle_var(char **new_buf, char *buf, int idx, int start)
{
	char	*key;

	if (is_num(buf[idx]))
	{
		if (buf[idx++] == '0')
			*new_buf = strjoin_s(*new_buf, "minishell", true);
		else
			*new_buf = strjoin_s(*new_buf, "", true);
	}
	else if (is_alpha(buf[idx]) || buf[idx] == '_')
	{
		while (is_alpha(buf[idx]) || is_num(buf[idx]) || buf[idx] == '_')
			++idx;
		key = ft_substr2(buf, start, idx);
		if (key)
		{
			if (get_var(g_envp, key))
				*new_buf = strjoin_s(*new_buf, get_var(g_envp, key), true);
			else
				*new_buf = strjoin_s(*new_buf, "", true);
			free(key);
		}
	}
	return (idx);
}

char	*replace_var(char *buffer)
{
	t_bool	is_var;
	int		start;
	int		end;
	char	*new_buff;
	char	*key;

	end = 0;
	new_buff = NULL;
	is_var = false;
	while (buffer[end])
	{
		if (buffer[end] == '$' && (is_alpha(buffer[end + 1])
			|| is_num(buffer[end + 1]) || buffer[end + 1] == '_'))
			is_var = true;
		if (!is_var && buffer[end] != '\0')
		{
			new_buff = strjoin_c(new_buff, buffer[end++], true);
			continue ;
		}
		start = ++end;
		end = handle_var(&new_buff, buffer, end, start);
		is_var = false;
		// if (is_num(buffer[end]))
		// {
		// 	if (buffer[end++] == '0')
		// 		new_buff = strjoin_s(new_buff, "minishell", true);
		// 	else
		// 		new_buff = strjoin_s(new_buff, "", true);
		// 	//is_var = false;
		// }
		// else if (is_alpha(buffer[end]) || buffer[end] == '_')
		// {
		// 	while (is_alpha(buffer[end]) || is_num(buffer[end]) || buffer[end] == '_')
		// 		++end;
		// 	key = ft_substr2(buffer, start, end);
		// 	if (key)
		// 	{
		// 		if (get_var(g_envp, key))
		// 			new_buff = strjoin_s(new_buff, get_var(g_envp, key), true);
		// 		else
		// 			new_buff = strjoin_s(new_buff, "", true);
		// 	}
		// 	//is_var = false;
		// }
	}
	free(buffer);
	return (new_buff);
}

int 	open_heredoc(char *delim)
{
	int 	fd;
	char 	*buffer;
	t_bool	exit_by_delim;

	exit_by_delim = false;
	fd = open("/tmp/.HEREDOC", O_CREAT | O_TRUNC | O_RDWR,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(2, "> ", 2);
	while(true)
	{
		if (get_next_line(&buffer) <= 0)
			break ;
		if (strcmp(delim, buffer) == 0)
		{
			exit_by_delim = true;
			break ;
		}
		buffer = replace_var(buffer);
		write(fd, buffer, strlen(buffer));
		write(fd, "\n", 1);
		write(2, "> ", 2);
	}
	close(fd);
	if (!exit_by_delim)
		p_error("warning", "here-document delimited by end-of-file wanted", delim, 0);
	fd = open("/tmp/.HEREDOC", O_RDONLY);
	return (fd);
}

int		fill_envp(char **envp)
{
	int		i;
	int		shlvlv;
	t_var	*shlvl_var;

	i = -1;
	if (!envp)
		return (1);
	g_envp = new_vector();
	while (envp[++i] != NULL)
		insert(g_envp, split_key_value_v(envp[i]));
	insert(g_envp, new_var_kv("?", "0"));
	shlvl_var = get_var_2(g_envp, "SHLVL");
	if (shlvl_var != NULL && shlvl_var->value != NULL) {
		shlvlv = atoi(shlvl_var->value);
		shlvlv++;
		// covert back to string and insert in shlvl_var
		set_var2(g_envp, "SHLVL", ft_itoa(shlvlv));
	}
	return (0);
}

char	*to_string(void *item)
{
	char *it = (char *)item;
	return (strcat(it, "\n"));
}

int get_position(t_size size, int index)
{
	if (size == 1)
		return (IS_FIRSTLAST);
	if (index == 0)
		return (IS_FIRST);
	if (index == size - 1)
		return (IS_LAST);
	return (IS_MIDDLE);
}

void setup_redirection(t_type type, char *arg, int *sout, int *sin)
{
	// int flags;
	int fd;

	if (type == RIGHT)
		fd = open(arg, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == RIGHT_APPEND)
		fd = open(arg, O_CREAT | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == HEREDOC) {
		fd = open_heredoc(arg);
	}
	else if (type == LEFT)
		fd = open(arg, O_RDONLY);
	if (fd < 0)
		exit(1);
	if (type == RIGHT || type == RIGHT_APPEND)
	{
		*sout = dup(1);
		dup2(fd, 1);
		close(fd);
	}
	else if (type == LEFT || type == HEREDOC)
	{
		*sin = dup(0);
		dup2(fd, 0);
		close(fd);
	}
}

void restore_redirs(int sout, int sin)
{
	if (sout != -1)
	{
		dup2(sout, 1);
		close(sout);
	}
	if (sin != -1)
	{
		dup2(sin, 0);
		close(sin);
	}
}

void setup_all_redirs(t_vector *redirs, int *sout, int *sin)
{
	int i;
	t_redir *redir;

	i = -1;
	while (++i < redirs->size)
	{
		restore_redirs(*sout, *sin);
		redir = (t_redir *) at(redirs, i);
		setup_redirection(redir->type, redir->arg, sout, sin);
		free(redir->arg);
	}
}

void setup_pipes(int fd[][2], int position, int index)
{
	const int prev_idx = index - 1;

	if (position == IS_FIRST)
	{
		dup2(fd[index][1], 1);
		close(fd[index][0]);
	}
	else if (position == IS_MIDDLE)
	{
		dup2(fd[prev_idx][0], 0);
		dup2(fd[index][1], 1);
		close(fd[index][0]);
		close(fd[prev_idx][1]);
	}
	else if (position == IS_LAST)
	{
		dup2(fd[prev_idx][0], 0);
		close(fd[prev_idx][1]);
		close(fd[index][1]);
		close(fd[index][0]);
	}
	close(fd[index][1]);
	close(fd[index][0]);
}

void close_pipes(int fd[][2], int pos, int index)
{
	if (pos == IS_FIRST)
		close(fd[index][1]);
	if (pos == IS_MIDDLE)
	{
		close(fd[index - 1][0]);
		close(fd[index][1]);
	}
	if (pos == IS_LAST)
		close(fd[index - 1][0]);
}

pid_t run_cmd_parent(t_cmd *cmd)
{
	int	sout;
	int sin;

	sout = -1;
	sin = -1;
	if (cmd->redirs != NULL && !is_empty(cmd->redirs))
		setup_all_redirs(cmd->redirs, &sout, &sin);
	exec_cmd(cmd);
	// Set $? Accordingly
	restore_redirs(sout, sin);
	// unlink("/tmp/.HEREDOC");
	return -1;
}

pid_t run_cmd_child(t_cmd *cmd, int fd[][2], t_size size, int index)
{
	pid_t pid;
	int pos;
	int sout;
	int sin;

	sin = -1;
	sout = -1;
	if ((pid = fork()) < 0)
		ft_exit("Error\nFORK FAILED!", -1);
	g_is_forked = true;
	pos = get_position(size, index);
	if (pid == 0)
	{
		setup_pipes(fd, pos, index);
		if (cmd->redirs != NULL && !is_empty(cmd->redirs))
			setup_all_redirs(cmd->redirs, &sout, &sin);
		exit(exec_cmd(cmd));
	}
	// unlink("/tmp/.HEREDOC");
	close_pipes(fd, pos, index);
	return pid;
}

void  run_cmds(t_vector *cmds)
{
	int i;
	int fd[1024][2];
	pid_t pids[1024];
	t_cmd	*cmd;

	i = -1;
	cmd = (t_cmd *) at(cmds, 0);
	if (cmds->size == 1 && is_builtin(cmd->argv[0]))
	{
		pids[0] = run_cmd_parent(cmd);
	}
	else
	{
		while (++i < cmds->size)
		{
			pipe(fd[i]);
			t_cmd *cmd = (t_cmd *)at(cmds, i);
			pids[i] = run_cmd_child(cmd, fd, cmds->size, i);
		}
	}
	i = -1;
	while (++i < cmds->size)
		if (pids[i] > 0)
			wait(&pids[i]);
	g_is_forked = false;
}

t_redir *create_redir(t_type type, char *arg)
{
	t_redir *r = malloc(sizeof(t_redir));
	r->arg = strdup(arg);
	r->type = type;
	return (r);
}

