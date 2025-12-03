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

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra

SOURCES := \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c
OBJECTS := $(SOURCES:.c=.o)
BONUS_SOURCES := \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c
BONUS_OBJECTS := $(BONUS_SOURCES:.c=.o)

TEST_SOURCES = $(SOURCES) $(BONUS_SOURCES) \
	test/test.c
TEST_OBJECTS := $(TEST_SOURCES:.c=.o)

test: CFLAGS += -ldl -rdynamic -D_GNU_SOURCE -DFT_ENABLE_TESTS
#bonus: CFLAGS += -DLIBFT_BONUS

# Rule to transform any .c →  .o
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

.PHONY: bonus
bonus: $(OBJECTS) $(BONUS_OBJECTS)
	ar rcs $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

.PHONY: test
test: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o tests

$(NAME): all

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(TEST_OBJECTS)
	rm -f $(BONUS_OBJECTS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f tests

.PHONY: re
re: fclean all
