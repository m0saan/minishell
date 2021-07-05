#include "../include/error.h"
#include "../include/minishell.h"

t_error	*create_error(void)
{
	t_error	*error;

	error = malloc(sizeof(t_error));
	ft_memset(error, 0, sizeof(t_error));
	return (error);
}

void	set_error(t_error *error, char *msg)
{
	error->is_error = true;
	error->error_msg = msg;
}

int		p_error(const char *arg, 
		const char *arg2, const char *message, int code)
{
	write(2, "minishell: ", 11);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (arg2)
	{
		write(2, arg2, ft_strlen(arg2));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (code);
}

void	handle_errors(t_cmd *cmd, t_bool ispath, int errno_)
{
	struct stat dir_stat;

	if (ispath && stat(cmd->argv[0], &dir_stat) == 0
		&& S_ISDIR(dir_stat.st_mode))
		exit(p_error(cmd->argv[0], NULL, "is a directory", 126));
	if (errno_ == 13)
		exit(p_error(cmd->argv[0], NULL, NULL, 126));
	else if (errno_ == 8)
		exit(p_error(cmd->argv[0], NULL, NULL, 1));
	else if (ispath || get_var(g_config.envp, "PATH") == NULL)
		exit(p_error(cmd->argv[0], NULL, NULL, 127));
	else
		exit(p_error(cmd->argv[0], NULL, "command not found", 127));
}
