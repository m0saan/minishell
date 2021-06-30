all: minishell.c utility/ft_vector.c
	@rm -rf a.out
	@gcc -g3 -fsanitize=address -lreadline -L /Users/moboustt/.brew/opt/readline/lib/ -I/Users/moboustt/.brew/opt/readline/include/ \
		minishell.c execute.c utility/ft_vector.c utility/ft_env.c utility/ft_execve.c commands/*.c tokenizer/*.c parser/*.c libft/*.c lexer/*.c errors/*.c ast/*.c -o minishell

