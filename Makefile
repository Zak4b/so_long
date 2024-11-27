NAME = so_long

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror
LIBFLAGS = -L./minilibx-linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz

SOURCES = \
	main.c \
	map_parsing.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	@cc $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJS) $(LIBFT) minilibx-linux/libmlx.a

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@cc $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft all

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all