#include "../include/minishell.h"

void	signal_handler_parent(int sig)
{
	if (sig == SIGQUIT && g_config.is_forked)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
	if (sig == SIGQUIT && !g_config.is_forked)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT && g_config.is_forked)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	if (sig == SIGINT && !g_config.is_forked)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		update_status_code(1);
	}
}

void	update_status_code(int code)
{
	char	*code_str;

	if (code >= 0)
	{
		code_str = ft_itoa(code);
		set_var2(g_config.envp, "?", code_str, false);
	}
	else
	{
		code_str = ft_itoa(WEXITSTATUS(g_config.status));
		set_var2(g_config.envp, "?", code_str, false);
	}
	if (code_str)
		free(code_str);
}

void	ft_init(char **env, int ac, char **av)
{
	ac = 0;
	av = NULL;
	g_config.is_forked = false;
	fill_envp(env);
	g_config.prompt = strjoin_s(get_var(g_config.envp, "PWD"), " _$ ", false);
	signal(SIGQUIT, signal_handler_parent);
	signal(SIGINT, signal_handler_parent);
}
