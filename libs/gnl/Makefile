# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgamba <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 20:47:34 by lgamba            #+#    #+#              #
#    Updated: 2024/11/06 16:08:51 by lgamba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES := \
./get_next_line.c \
./get_next_line_utils.c

OBJECTS := $(SOURCES:.c=.o)

# Rule to transform any .c →  .o
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(NAME): all

.PHONY: clean
clean:
	rm -f $(OBJECTS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
