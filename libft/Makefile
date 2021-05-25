# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moboustt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/28 19:12:03 by moboustt          #+#    #+#              #
#    Updated: 2019/10/29 15:40:27 by moboustt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- This is a MakeFile -*-
NAME= libft.a
_CC= gcc
_CFLAGS=-Wall -Werror -Wextra
_SOURCES= ft_strmapi.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_bzero.c ft_memmove.c ft_strdup.c ft_atoi.c ft_isdigit.c ft_strlcat.c ft_split.c ft_strnstr.c ft_isalnum.c ft_isprint.c ft_strlcpy.c ft_strrchr.c ft_isalpha.c ft_memset.c ft_strlen.c ft_tolower.c ft_isascii.c ft_strchr.c ft_strncmp.c ft_toupper.c

all: $(NAME)

$(NAME): $(_SOURCES)
	@$(_CC) $(_CFLAGS) -c $(_SOURCES)
	@ar rc $(NAME) *.o

# The cleaner
# Delete all binaries and any editor backups of source and header files

clean: 
	@rm -rf *.o
	@echo "Makefile : Cleaning .o files..."

fclean: clean
	@rm -rf $(NAME) *.a
	@echo "Makefile : Clean .a files..."

re: fclean all

