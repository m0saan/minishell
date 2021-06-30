#include "error.h"

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

int		p_error(char *arg, char *message, int code)
{
	write(2, "minishell: ", 11);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (code);
}