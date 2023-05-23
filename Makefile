# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 14:02:59 by afalconi          #+#    #+#              #
#    Updated: 2023/05/23 09:37:25 by afalconi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = main.c utils.c utils2.c child.c utils3.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJ = $(CFILES:.c=.o)

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
RM = rm -rf

NAME = pipex

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

bonus: $(NAME)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
