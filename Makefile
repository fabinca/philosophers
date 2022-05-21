# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 14:57:03 by cfabian           #+#    #+#              #
#    Updated: 2022/05/22 00:59:47 by cfabian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src
SRC	= 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/forks.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/time.c \
		$(SRC_DIR)/philo.c \
		$(SRC_DIR)/philo_action.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/sleep.c \
		$(SRC_DIR)/safe_print.c \
		$(SRC_DIR)/ft_str_is_numeric.c
		
OBJ_DIR = obj
OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
CFLAGS	= -Wall -Werror -Wextra
CC = gcc
NAME = philo

all	: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(NAME)	: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

threadcheck	: 
	$(CC) $(SRC) $(CFLAGS) -fsanitize=thread -lpthread  -g -o threadcheck
	./threadcheck 4 430 200 200 1

memcheck: all
	valgrind ./philo
	valgrind ./philo 2 8100 200 200 1

norm:
	norminette $(SRC) $(INCL)

.PHONY: all memcheck clean fclean re norm threadcheck
