cmake_minimum_required(VERSION 3.17)
project(MINISHELL)

add_executable(MINISHELL ./lexer/lexer.c lexer/lexer_helper_functions2.c lexer/lexer_helper_functions.c ./execute.c ./tokenizer/token.c
        ./parser/parse.c ./ast/node.c ./commands/ft_echo.c ./commands/ft_cd.c ./commands/ft_unset.c
        ./commands/ft_env.c ./commands/ft_pwd.c ./commands/ft_exit.c ./commands/ft_export.c  ./errors/error.c
        ./utility/ft_vector.c ./utility/ft_execve.c ./utility/ft_env.c ./minishell.c lexer/lexer_parsing_helper_funcs.c lexer/quotes_parsing_helper_funcs.c lexer/envirement_vars_utils.c lexer/env_vars_helper_funcs.c lexer/lexer_tokens_helper_funcs.c lexer/lexer_tokens_helper_funcs2.c parser/parser_helper_functions.c global_utils/global_utils.c global_utils/global_utils.h utility/vector_functions_implemet.c utility/vector_functions_implemt2.c global_utils/global_utils2.c)

target_link_libraries(MINISHELL ${CMAKE_SOURCE_DIR}/libft/libft.a)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -O0 -fsanitize=address -g3 -l readline -L /Users/moboustt/.brew/opt/readline/lib/ -I /Users/moboustt/.brew/opt/readline/include/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")