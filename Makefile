NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Wconversion -Werror -pedantic -std=gnu99
IFLAGS :=
LFLAGS := -lm


# :^ `.!find src -name "*.c" -exec echo "{} \\" \;`
SOURCES := $(shell find src -name '*.c')
SOURCES_BONUS := $(shell find bonus -name '*.c')

# Objects
OBJECTS := $(addprefix build/,$(SOURCES:.c=.o))
OBJECTS_BONUS := $(addprefix build/,$(SOURCES_BONUS:.c=.o))
# Libraries
LIB_FT := ./libs/libft/libft.a
IFLAGS += -I$(dir $(LIB_FT))
LIB_GNL := ./libs/gnl/libgnl.a
IFLAGS += -I$(dir $(LIB_GNL))
LIB_MLX := ./libs/minilibx-linux/libmlx_Linux.a
IFLAGS += -I$(dir $(LIB_MLX))

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Default target
$(NAME): LFLAGS += $(LIB_FT) $(LIB_GNL) $(LIB_MLX) -L/usr/lib -lXext -lX11
$(NAME): IFLAGS += -I./src
$(NAME): CFLAGS += -O2
$(NAME): $(LIB_FT) $(LIB_GNL) $(LIB_MLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

# Bonus
.PHONY: bonus
bonus: LFLAGS += $(LIB_FT) $(LIB_GNL) $(LIB_MLX) -L/usr/lib -lXext -lX11
bonus: IFLAGS += -I./bonus
bonus: CFLAGS += -O2
bonus: $(LIB_FT) $(LIB_GNL) $(LIB_MLX) $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJECTS_BONUS) $(LFLAGS)

.PHONY: fast-clang
fast-clang: LFLAGS += $(LIB_FT) $(LIB_GNL) $(LIB_MLX) -L/usr/lib -lXext -lX11
fast-clang: IFLAGS += -I./bonus
fast-clang: CFLAGS += -O3 -Ofast -march=native -mtune=native -ffast-math -funroll-loops -fomit-frame-pointer -DNDEBUG -pthread -flto
fast-clang: $(LIB_FT) $(LIB_GNL) $(LIB_MLX)
	clang $(CFLAGS) $(IFLAGS) $(SOURCES_BONUS) -o $(NAME) $(LFLAGS)

.PHONY: fast-gcc
fast-gcc: LFLAGS += $(LIB_FT) $(LIB_GNL) $(LIB_MLX) -L/usr/lib -lXext -lX11
fast-gcc: IFLAGS += -I./bonus
fast-gcc: CFLAGS += -O3 -Ofast -march=native -mtune=native -ffast-math -funroll-loops -fomit-frame-pointer -DNDEBUG -pthread -flto
fast-gcc: $(LIB_FT) $(LIB_GNL) $(LIB_MLX)
	gcc $(CFLAGS) $(IFLAGS) $(SOURCES_BONUS) -o $(NAME) $(LFLAGS)

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
	cd $(dir $(LIB_MLX)) && CFLAGS="-std=c89" ./configure

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
