NAME = so_long

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror -g
LIBFLAGS = -L./minilibx-linux -L/usr/lib -lmlx -lXext -lX11 -lm -lz

SOURCES = \
	main.c \
	event_hooks.c \
	map_parsing.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	@cc $(FLAGS) $(LIBFLAGS) -o $(NAME) $(OBJS) $(LIBFT) minilibx-linux/libmlx.a
	@echo "Done"

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