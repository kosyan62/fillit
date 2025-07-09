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

include libft/libft/libft.mk

NAME = fillit

BUILD_DIR = build

SRCS = main.c tetramino.c validator.c
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_LNK)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(BUILD_DIR)/%.o: %.c header.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< $(LIBFT_INC) -o $@

clean:
	rm -rvf $(BUILD_DIR)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -rvf $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
