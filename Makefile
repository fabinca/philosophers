# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 14:57:03 by cfabian           #+#    #+#              #
#    Updated: 2022/05/21 15:57:05 by cfabian          ###   ########.fr        #
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
		$(SRC_DIR)/ft_str_is_numeric.c
		
OBJ_DIR = obj
OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
CFLAGS	= -Wall -Werror -Wextra
CC = gcc
NAME = philo

all	: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(NAME)	: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -lpthread -g -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

threadcheck	: 
	$(CC) $(SRC) $(CFLAGS) -fsanitize=thread -lpthread  -g -o threadcheck
	./threadcheck 4 430 1 1 200

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 4 410 200 200 1

norm:
	norminette $(SRC) $(INCL)

.PHONY: all memcheck clean fclean re norm threadcheck
