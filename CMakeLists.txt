cmake_minimum_required(VERSION 3.19)
project(minishell C)

add_executable(minishell minishell.c minishell.h lexer/lexer.c parser/parse.c
        parser/parser_utils.c tokenizer/token.c ast/node.c utility/ft_vector.c
        utility/ft_vector.h ast/node.h lexer/lexer.h execute.c errors/error.c
        commands/ft_cd.c
        commands/ft_echo.c
        commands/ft_env.c
        commands/ft_exit.c
        commands/ft_pwd.c
        commands/ft_unset.c
        commands/ft_export.c
        utility/ft_env.c
        utility/ft_vector.c
        utility/ft_env.c
        utility/ft_execve.c
        utility/ft_vector.c
        )

target_link_libraries(minishell ${CMAKE_SOURCE_DIR}/libft/libft.a)

set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address -g3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
