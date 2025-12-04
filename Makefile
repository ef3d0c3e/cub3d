NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -pedantic -ggdb -std=gnu99
IFLAGS := -I./src
LFLAGS := -lm


# :^ `.!find src -name "*.c" -exec echo "{} \\" \;`
SOURCES := $(shell find src -name '*.c')

# Objects
OBJECTS := $(addprefix build/,$(SOURCES:.c=.o))
# Libraries
LIB_FT := ./libs/libft/libft.a
IFLAGS += -I$(dir $(LIB_FT))/
LIB_GNL := ./libs/gnl/libgnl.a
IFLAGS += -I$(dir $(LIB_GNL))/
LIB_MLX := ./libs/minilibx-linux/libmlx_Linux.a
IFLAGS += -I$(dir $(LIB_MLX))/

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Default target
$(NAME): LFLAGS += $(LIB_FT) $(LIB_GNL) $(LIB_MLX) -L/usr/lib -lXext -lX11
$(NAME): $(LIB_FT) $(LIB_GNL) $(LIB_MLX) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

# Bonus
.PHONY: all
bonus: $(NAME)

# All
.PHONY: all
all: $(NAME)

# Libraries build
# libft
$(LIB_FT):
	echo "Building libft..."
	$(MAKE) -C $(dir $(LIB_FT))

# ft_gnl
$(LIB_GNL):
	echo "Building gnl..."
	$(MAKE) -C $(dir $(LIB_GNL))

# MLX
$(LIB_MLX):
	echo "Building libmlx..."
	cd $(dir $(LIB_MLX)) && CFLAGS="-std=gnu89" ./configure

.PHONY: clangd
clangd:
	@mkdir -p build
	cd build && cmake ..
	cp build/compile_commands.json .

.PHONY: docs
docs:
	@mkdir -p docs
	doxygen doxygen

.PHONY: clean
clean:
	$(RM) -r build/

.PHONY: lclean
lclean:
	echo "Cleaning libft..."
	cd $(dir $(LIB_FT)) && make fclean
	echo "Cleaning gnl..."
	cd $(dir $(LIB_GNL)) && make fclean
	echo "Cleaning mlx..."
	cd $(dir $(LIB_MLX)) && make clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
