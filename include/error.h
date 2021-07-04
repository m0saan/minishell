#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_types.h"
# include "ft_globals.h"

# define ERR1 "syntax error near unexpected token"

typedef struct s_error
{
	t_bool	is_error;
	char	*error_msg;
}			t_error;

void		set_error(t_error *error, char *msg);
t_bool		check_entered_command(const char *line);
t_error		*create_error(void);
int			p_error(const char *arg, const char *arg2,
				const char *message, int code);

#endif
