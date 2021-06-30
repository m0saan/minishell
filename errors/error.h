#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include "../utility/ft_types.h"
# include "../global_utils/global_utils.h"

# define ERR1 "syntax error near unexpected token"

typedef struct s_error
{
	t_bool	is_error;
	char	*error_msg;
}			t_error;

void		set_error(t_error *error, char *msg);
t_bool		check_entered_command(const char *line);
t_error		*create_error(void);
int			p_error(char *arg, char *message, int code);

#endif
