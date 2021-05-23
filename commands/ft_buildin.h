#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "../minishell.h"

int		ft_cd(int ac, char **av);
int		ft_echo(int ac, char **av);
int		ft_export(int ac, char **av);
int		ft_unset(int ac, char **av);
int		ft_exits(int ac, char **av);
int		ft_env(int ac, char **av);
int		ft_pwd(int ac, char **av);

#endif