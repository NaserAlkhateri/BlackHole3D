# **************************************************************************** #
#                                   cub3D                                       #
# **************************************************************************** #

NAME        := cub3D
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCDIR      := include
SRCDIR      := srcs
OBJDIR      := objs
LIBFT_DIR   := $(SRCDIR)/libft
MLX_DIR     := $(SRCDIR)/mlx

LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_A       := $(MLX_DIR)/libmlx.a

# add load_textures.c here
SRC_FILES := main.c init_mlx.c render.c hooks.c parse_scene.c \
             load_textures.c map_parse.c player.c raycast.c controls.c
SRCS        := $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJS        := $(addprefix $(OBJDIR)/,$(SRC_FILES:.c=.o))

UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLX_LDFLAGS := -framework OpenGL -framework AppKit
else
	MLX_LDFLAGS := -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJDIR) $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) \
		-I$(INCDIR) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx \
		$(MLX_LDFLAGS) \
		-o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/cub3d.h
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# auto-pickup GNL from libft if present
GNL_SRCS    := $(wildcard $(LIBFT_DIR)/get_next_line*.c)
GNL_OBJS    := $(patsubst $(LIBFT_DIR)/%.c,$(OBJDIR)/%.o,$(GNL_SRCS))
$(OBJDIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean || true
	rm -f $(NAME)

re: fclean all
bonus: all

.PHONY: all clean fclean re bonus
