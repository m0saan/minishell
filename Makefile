all: minishell.c utility/ft_vector.c
	@rm -rf a.out
	@gcc minishell.c utility/ft_vector.c

