NAME = cub3D

CFLAGS = -Wall -Werror -Wextra

CC = cc

SRCSDIR = srcs

OBJSDIR = objs

MLXDIR = srcs/mlx

LIBFTDIR = srcs/libft

LIBFT = $(LIBFTDIR)/libft.a

SOURCES = $(SRCSDIR)/main.c

OBJECTS = $(SOURCES:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	make -C $(LIBFTDIR)
	make -C $(MLXDIR)
	$(CC) $(OBJECTS) $(CFLAGS) -I$(MLXDIR) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(LIBFT)

clean:
	rm -rf $(OBJSDIR)
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all
