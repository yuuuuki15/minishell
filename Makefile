NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS_DIR = obj
SRCS_DIR = src
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
SRCS = main.c
LIBFT = libft/libft.a
RM = rm -rf

all : $(NAME)
$(NAME): $(OBJS)
	make libft.a -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
re: fclean all
clean:
	make clean -C libft
	$(RM) $(OBJS_DIR)
fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
.PHONY: all $(NAME) re clean fclean
