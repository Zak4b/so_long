NAME = so_long

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./minilibx-linux -lmlx -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm -lz

SOURCES = \
	main.c \
	map_parsing.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	cc $(FLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) libft/libft.a

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@cc $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft all

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all