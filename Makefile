NAME = so_long

GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

LIBFT = libft/libft.a
MLX_FOLDER = minilibx-linux
MLX = $(MLX_FOLDER)/libmlx.a
INC = -I./$(MLX_FOLDER) -I./libft -I./
LIB = -L./$(MLX_FOLDER) -L/usr/lib -lmlx -lXext -lX11 -lm -lz -L./libft/ -lft

FLAGS = -Wall -Wextra -Werror -O3

SOURCES = \
	main.c \
	event_hooks.c \
	game.c \
	render.c \
	map_utils.c \
	map_parser.c \
	map_checker.c \
	mlx_img_utils.c \
	mlx_img_utils2.c \
	distance.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): update_submodules $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@cc $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(LIB)
	@echo "$(GREEN)Compilation finished successfully!$(RESET)"

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@cc $(FLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building Libft...$(RESET)"
	@make -s -C libft all

$(MLX):
	@echo "$(GREEN)Building minilibx...$(RESET)"
	@make -s -C $(MLX_FOLDER) all

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME)
	@make -s -C $(MLX_FOLDER) clean
	@make -s -C libft fclean

re: fclean all

norm:
	norminette srcs libft *.h *.c

update_submodules:
	git submodule update --init --recursive

.PHONY: all clean fclean re
