# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/04 19:30:39 by ehakam            #+#    #+#              #
#    Updated: 2021/07/14 13:08:34 by ehakam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
LRL			=	"-lreadline"
LDFLAGS		=	"-L/goinfre/$(USER)/.brew/opt/readline/lib"
CPPFLAGS	=	"-I/goinfre/$(USER)/.brew/opt/readline/include"

SRC_LEXER	=	lexer/envirement_vars_utils.c \
				lexer/lexer.c \
				lexer/env_vars_helper_funcs.c \
				lexer/lexer_helper_functions.c \
				lexer/lexer_helper_functions2.c \
				lexer/lexer_tokens_helper_funcs.c \
				lexer/lexer_tokens_helper_funcs2.c \
				lexer/lexer_parsing_helper_funcs.c \
				lexer/quotes_parsing_helper_funcs.c
				
SRC_PARSER	=	parser/parse.c \
				parser/parse_redirs.c \
				parser/parser_helper_functions.c \
				parser/vector_fill_out_utils.c
				
SRC_UTILS	=	global_utils/ft_atoi.c \
				global_utils/ft_atol.c \
				global_utils/ft_bzero.c \
				global_utils/ft_is.c \
				global_utils/ft_itoa.c \
				global_utils/ft_memset.c \
				global_utils/ft_split.c \
				global_utils/ft_strcmp.c \
				global_utils/ft_strdup.c \
				global_utils/ft_strjoin.c \
				global_utils/ft_strlen.c \
				global_utils/ft_substr.c \
				global_utils/ft_index_of.c \
				global_utils/gnl.c \
				global_utils/ft_malloc.c

SRC_BUILTINS=	builtins/ft_cd.c \
				builtins/ft_echo.c \
				builtins/ft_env.c \
				builtins/ft_exit.c \
				builtins/ft_export.c \
				builtins/ft_pwd.c \
				builtins/ft_unset.c

SRC_EXEC	=	main/ft_cmds.c \
				main/ft_envp.c \
				main/ft_paths.c \
				main/ft_execve.c \
				main/ft_pipes.c \
				main/ft_redirs.c \
				main/ft_run.c \
				main/minishell.c \
				main/ft_signals.c \
				main/ft_vector.c \
				main/ft_vector_1.c \
				main/ft_vector_2.c \
				main/ft_heredoc.c \
				main/ft_heredoc_handlers.c \
				main/ft_variables.c \
				main/ft_variables_2.c \
				main/ft_variables_3.c \
				main/ft_variables_4.c \
				main/ft_free.c \


SRC_AST		=	ast/node.c
SRC_ERRORS	=	errors/error.c
SRC_TOKEN	=	tokenizer/token.c

SRCS		=	$(SRC_LEXER) $(SRC_PARSER) $(SRC_UTILS) $(SRC_BUILTINS)	$(SRC_EXEC) $(SRC_AST) $(SRC_ERRORS) $(SRC_TOKEN)

all: $(NAME)

$(NAME): $(SRCS)
	@echo "Building..."
	@gcc $(CFLAG) $(LRL) $(LDFLAGS) $(CPPFLAGS) $(SRCS) -o $(NAME)
	
clean:
	@echo "Cleaning..."
	@rm -rf *.o

fclean: clean
	@echo "Full Cleaning..."
	@rm -rf $(NAME) *.out

re: fclean all
