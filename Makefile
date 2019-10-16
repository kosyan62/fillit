# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkingsbl <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 16:27:53 by pkingsbl          #+#    #+#              #
#    Updated: 2019/10/16 21:38:38 by mgena            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

PATH_LIBFT = libft

SRC = main.c tetramino.c validator.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(PATH_LIBFT)/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(PATH_LIBFT) -lft

$(PATH_LIBFT)/libft.a:
	make -C $(PATH_LIBFT)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -I $(PATH_LIBFT)

clean:
	rm -f $(OBJ)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(PATH_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
