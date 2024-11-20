NAME = so_long

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror

SOURCES = main.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	cc -o $(NAME) $(OBJS) libft/libft.a 

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