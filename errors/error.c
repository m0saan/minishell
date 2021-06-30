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