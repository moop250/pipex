# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 16:16:12 by hlibine           #+#    #+#              #
#    Updated: 2024/02/14 11:38:01 by hlibine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
EXTENDED_FT = srcs/extended_ft/
BONUS = pipex_bonus

SRCS_PX = srcs/pipex.c \

SRCS = srcs/px_utils.c \
		srcs/px_cmdprocess.c \

BONUS_SRCS = bonus/pipex_bonus.c \
		bonus/bonus_utils.c \
		bonus/get_next_line/get_next_line_utils.c \
		bonus/get_next_line/get_next_line.c \

INCLUDE = -L ./srcs/extended_ft/ -lft

GREEN = \033[0;32m
ORANGE = \033[38;5;208m
RESET = \033[0m

${NAME}: ${SRCS_PX} ${SRCS}
		@echo "$(ORANGE)Building extended_ft$(RESET)"
		@make -s -C ${EXTENDED_FT}
		@echo "$(GREEN)extended_ft built$(RESET)"
		@echo "$(ORANGE)Building $(NAME)$(RESET)"
		@${CC} ${CFLAGS} ${SRCS_PX} ${SRCS} -o ${NAME} ${INCLUDE}
		@echo "$(GREEN)$(NAME) built$(RESET)"

${BONUS}: ${SRCS} ${BONUS_SRCS}
		@echo "$(ORANGE)Building extended_ft$(RESET)"
		@make -s -C ${EXTENDED_FT}
		@echo "$(GREEN)extended_ft built$(RESET)"
		@echo "$(ORANGE)Building $(BONUS)$(RESET)"
		@${CC} ${CFLAGS} ${BONUS_SRCS} ${SRCS} -o ${BONUS} ${INCLUDE}
		@echo "$(GREEN)$(BONUS) built$(RESET)"

all: ${NAME} ${BONUS}

bonus: ${BONUS}

clean:
		@echo "$(ORANGE)Cleaning up$(RESET)"
		@cd $(EXTENDED_FT) && $(MAKE) -s clean
		@echo "$(GREEN)Clean up successful$(RESET)"

fclean: clean
		@echo "$(ORANGE)Full clean up$(RESET)"
		@${RM} ${NAME} ${BONUS}
		@cd $(EXTENDED_FT) && $(MAKE) -s fclean
		@echo "$(GREEN)Full clean up successful$(RESET)"

re: fclean all



.PHONY: all clean fclean re bonus