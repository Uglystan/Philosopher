# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucasgirault <lucasgirault@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 18:33:34 by lgirault          #+#    #+#              #
#    Updated: 2023/05/25 22:59:52 by lucasgiraul      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosopher
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
RM = rm -rf

GREEN=\033[33;32m
BLUE=\033[0;34m
BOLD=\033[1m
RESET=\033[0m

	
SRC = src/check_arg.c \
	src/Philosopher.c \
	src/utils.c \
	src/init.c \
	src/routine.c \

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ)  include/philosopher.h
	@echo "$(BLUE)$(BOLD)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) compiled!$(RESET)"

all: $(NAME)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(BLUE)$(BOLD)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re