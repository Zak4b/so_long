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
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFLAGS) $(LIBFT) minilibx-linux/libmlx.a
	@echo "$(GREEN)Compilation finished successfully!$(RESET)"

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@gcc $(FLAGS) -Iminilibx-linux -Ilibft -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building Libft...$(RESET)"
	@make -C libft all

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C libft clean

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
