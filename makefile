# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 18:45:14 by aaammari          #+#    #+#              #
#    Updated: 2023/03/10 22:59:36 by simoberri        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



LIB_LIBFT = libft/libft.a
HEADER = libft/libft.h parsing.h

NAME = minishell
SRC =	minishell.c 		\
		check_quotes.c		\
		expand.c			\
		redirect.c			\
		redir_append.c		\
		utils_dollar_qts.c	\
		expand_utils.c		\
		utils.c				\
		check_pipes.c		\
		check_redirect.c	\
		parse.c				\
		
OBJ = $(SRC:.c=.o)

%.o : %.c $(HEADER) 
	gcc -Wall -Wextra -Werror -c $< -o $@

all : LIBFTT $(NAME)

$(NAME) :  $(OBJ) 
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) $(LIB_LIBFT) -lreadline
	
LIBFTT : 
	make -C libft

clean :
	rm -f $(NAME) $(OBJ)
	make clean -C libft
	
fclean : clean
	make fclean -C libft

re : fclean all