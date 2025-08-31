NAME    := cub3D
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCS    := -Iinclude -Isrcs/libft -Isrcs/mlx

# libs (42 setup)
LIBFT   := srcs/libft/libft.a
MLX     := srcs/mlx/libmlx.a

# frameworks for macOS (your logs show AppKit/OpenGL)
LDFLAGS := $(MLX) $(LIBFT) -framework OpenGL -framework AppKit

SRCS := \
srcs/main.c \
srcs/init_mlx.c \
srcs/render.c \
srcs/hooks.c \
srcs/parse_scene.c \
srcs/load_textures.c \
srcs/map_parse.c \
srcs/player.c \
srcs/raycast.c \
srcs/raycast_utils.c \
srcs/raycast_utils2.c \
srcs/controls.c \
srcs/rgb_parse.c \
srcs/parse_utils.c \
srcs/parse_textures.c \
srcs/map_accumulate.c \
srcs/map_chars.c \
srcs/map_finalize.c \
srcs/parse_utils2.c

OBJS := $(SRCS:srcs/%.c=objs/%.o)

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LDFLAGS) -o $(NAME)

objs/%.o: srcs/%.c | objs
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

objs:
	mkdir -p objs

$(LIBFT):
	$(MAKE) -C srcs/libft

$(MLX):
	$(MAKE) -C srcs/mlx

clean:
	$(MAKE) -C srcs/libft clean
	$(MAKE) -C srcs/mlx clean || true
	rm -rf objs

fclean: clean
	$(MAKE) -C srcs/libft fclean
	rm -f $(MLX)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re