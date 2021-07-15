cmake_minimum_required(VERSION 3.17)
project(MINISHELL)


add_executable(
        MINISHELL ./ast/node.c
        ./builtins/ft_cd.c
        ./builtins/ft_echo.c
        ./builtins/ft_env.c
        ./builtins/ft_exit.c
        ./builtins/ft_export.c
        ./builtins/ft_pwd.c
        ./builtins/ft_unset.c
        ./errors/error.c
        ./global_utils/ft_atoi.c
        ./global_utils/ft_atol.c
        ./global_utils/ft_bzero.c
        ./global_utils/ft_index_of.c
        ./global_utils/ft_is.c
        ./global_utils/ft_itoa.c
        ./global_utils/ft_malloc.c
        ./global_utils/ft_memset.c
        ./global_utils/ft_split.c
        ./global_utils/ft_strcmp.c
        ./global_utils/ft_strdup.c
        ./global_utils/ft_strjoin.c
        ./global_utils/ft_strlen.c
        ./global_utils/ft_substr.c
        ./global_utils/gnl.c
        ./lexer/env_vars_helper_funcs.c
        ./lexer/envirement_vars_utils.c
        ./lexer/lexer.c
        ./lexer/lexer_helper_functions.c
        ./lexer/lexer_helper_functions2.c
        ./lexer/lexer_parsing_helper_funcs.c
        ./lexer/lexer_tokens_helper_funcs.c
        ./lexer/lexer_tokens_helper_funcs2.c
        ./lexer/quotes_parsing_helper_funcs.c
        ./main/ft_cmds.c
        ./main/ft_envp.c
        ./main/ft_execve.c
        ./main/ft_heredoc.c
        ./main/ft_heredoc_handlers.c
        ./main/ft_paths.c
        ./main/ft_pipes.c
        ./main/ft_redirs.c
        ./main/ft_run.c
        ./main/ft_signals.c
        ./main/ft_variables.c
        ./main/ft_variables_2.c
        ./main/ft_variables_3.c
        ./main/ft_variables_4.c
        ./main/ft_vector.c
        ./main/ft_vector_1.c
        ./main/ft_vector_2.c
        ./main/minishell.c
        ./parser/parse.c
        ./parser/parse_redirs.c
        ./parser/parser_helper_functions.c
        ./parser/vector_fill_out_utils.c
        ./tokenizer/token.c main/ft_free.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -O0 -g3 -fsanitize=address -l readline -L /Users/moboustt/.brew/opt/readline/lib/ -I /Users/moboustt/.brew/opt/readline/include/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")