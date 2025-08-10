# **************************************************************************** #
#                                   cub3D                                       #
# **************************************************************************** #

# Program
NAME        := cub3D

# Compiler & Flags (subject requires cc and these flags)
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# Dirs
INCDIR      := include
SRCDIR      := srcs
OBJDIR      := objs
LIBFT_DIR   := $(SRCDIR)/libft
MLX_DIR     := $(SRCDIR)/mlx

# Libraries
LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

# Sources (add new .c files here as we progress)
SRC_FILES   := main.c init_mlx.c render.c hooks.c parse_scene.c
SRCS        := $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJS        := $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))

# OS-specific MLX link flags
UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLX_LDFLAGS := -framework OpenGL -framework AppKit
else
	MLX_LDFLAGS := -lXext -lX11 -lm
endif

# Default rule
all: $(NAME)

# Link final binary
$(NAME): $(LIBFT_A) $(MLX_A) $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) \
		-I$(INCDIR) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx \
		$(MLX_LDFLAGS) \
		-o $@

# Objects dir
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile .c -> /objs/.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/cub3d.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Build libft using its own Makefile (subject requires this flow)
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# Build MiniLibX from sources
$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

# Cleaning
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean || true
	rm -f $(NAME)

re: fclean all

# Subject asks to have a 'bonus' rule even if empty now
bonus: all

.PHONY: all clean fclean re bonus
