# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 09:24:28 by mevonuk           #+#    #+#              #
#    Updated: 2024/02/28 15:48:31 by ykawakit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall
LDFLAGS	+= -lreadline

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./includes/\
				-I ./libft/

# Sources
SRC_PATH	=	src/
PARSER		=	$(addprefix parser/, parser.c putils.c make_strc.c)
BUILTIN		=	$(addprefix builtin/, manager.c cd.c echo.c env.c export.c unset.c)
SRC			=	exec.c main.c \
				utils.c env.c\
				$(PARSER) \
				$(BUILTIN)

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC)
	@echo "Minishell ready."

clean:
	clear
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing minishell..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: clean all

.PHONY: all re clean fclean
