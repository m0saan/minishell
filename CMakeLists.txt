cmake_minimum_required(VERSION 3.17)
project(MINISHELL)


add_executable(MINISHELL ./lexer/env_vars_helper_funcs.c
        ./lexer/lexer_helper_functions.c
        ./lexer/lexer.c
        ./lexer/quotes_parsing_helper_funcs.c
        ./lexer/lexer_tokens_helper_funcs2.c
        ./lexer/envirement_vars_utils.c
        ./lexer/lexer_tokens_helper_funcs.c
        ./lexer/lexer_helper_functions2.c
        ./lexer/lexer_parsing_helper_funcs.c
        ./tokenizer/token.c
        ./global_utils/ft_vector.c
        ./global_utils/ft_is.c
        ./global_utils/gnl.c
        ./global_utils/ft_atol.c
        ./global_utils/ft_strlen.c
        ./global_utils/ft_vector_2.c
        ./global_utils/ft_bzero.c
        ./global_utils/ft_strjoin.c
        ./global_utils/ft_heredoc_handlers.c
        ./global_utils/ft_variables_2.c
        ./global_utils/ft_vector_1.c
        ./global_utils/ft_index_of.c
        ./global_utils/ft_heredoc.c
        ./global_utils/ft_split.c
        ./global_utils/ft_memset.c
        ./global_utils/ft_substr.c
        ./global_utils/ft_variables_3.c
        ./global_utils/ft_variables.c
        ./global_utils/ft_strdup.c
        ./global_utils/ft_atoi.c
        ./global_utils/ft_itoa.c
        ./global_utils/ft_variables_4.c
        ./global_utils/ft_strcmp.c
        ./parser/parser_helper_functions.c
        ./parser/vector_fill_out_utils.c
        ./parser/parse_redirs.c
        ./parser/parse.c
        ./builtins/ft_echo.c
        ./builtins/ft_cd.c
        ./builtins/ft_unset.c
        ./builtins/ft_env.c
        ./builtins/ft_pwd.c
        ./builtins/ft_exit.c
        ./builtins/ft_export.c
        ./ast/node.c
        ./errors/error.c
        ./main/ft_cmds.c
        ./main/ft_redirs.c
        ./main/ft_envp.c
        ./main/ft_run.c
        ./main/ft_execve.c
        ./main/ft_paths.c
        ./main/ft_pipes.c
        ./main/minishell.c
        global_utils/ft_malloc.c)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -O0 -fsanitize=address -g3 -l readline -L /Users/moboustt/.brew/opt/readline/lib/ -I /Users/moboustt/.brew/opt/readline/include/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")