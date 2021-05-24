all: minishell.c utility/ft_vector.c
	@rm -rf a.out
	@gcc minishell.c utility/ft_vector.c utility/ft_env.c utility/ft_execve.c commands/*.c

