# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yahamdan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 12:18:11 by yahamdan          #+#    #+#              #
#    Updated: 2023/03/02 16:33:19 by yahamdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c pipex_utils.c split.c get_path.c
BSRC = \
		./pipex_bonus/pipex_utils.c 		\
		./pipex_bonus/split.c 				\
		./pipex_bonus/get_next_line.c		\
		./pipex_bonus/get_next_line_utils.c \
		./pipex_bonus/pipex_bonus.c 		\
		./pipex_bonus/get_path.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
	
all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus : $(BONUS)

$(BONUS) : $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $(NAME)

clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all