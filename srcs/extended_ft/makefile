# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 15:13:08 by hlibine           #+#    #+#              #
#    Updated: 2024/02/09 15:30:36 by hlibine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = extended_ft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = srcs/ft_atoi \
			srcs/ft_bzero \
			srcs/ft_calloc \
			srcs/ft_isalnum \
			srcs/ft_isalpha \
			srcs/ft_isascii \
			srcs/ft_isdigit \
			srcs/ft_isprint \
			srcs/ft_itoa \
			srcs/ft_memchr \
			srcs/ft_memcmp \
			srcs/ft_memcpy \
			srcs/ft_memmove \
			srcs/ft_memset \
			srcs/ft_putchar_fd \
			srcs/ft_putendl_fd \
			srcs/ft_putnbr_fd \
			srcs/ft_putstr_fd \
			srcs/ft_split \
			srcs/ft_strchr \
			srcs/ft_strdup \
			srcs/ft_striteri \
			srcs/ft_strjoin \
			srcs/ft_strlcat \
			srcs/ft_strlcpy \
			srcs/ft_strlen \
			srcs/ft_strmapi \
			srcs/ft_strncmp \
			srcs/ft_strnstr \
			srcs/ft_strrchr \
			srcs/ft_strtrim \
			srcs/ft_substr \
			srcs/ft_tolower \
			srcs/ft_toupper \
			srcs/ft_realloc \
			srcs/ft_3dfree \
			srcs/garbage_collecter \
			srcs/gargabe_collector_utils \
			srcs/ft_lstnew \
			srcs/ft_lstadd_front \
			srcs/ft_lstsize \
			srcs/ft_lstlast \
			srcs/ft_lstadd_back \
			srcs/ft_lstdelone \
			srcs/ft_lstclear \
			srcs/ft_lstiter \
			srcs/ft_lstmap \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^
	

all: $(NAME)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re