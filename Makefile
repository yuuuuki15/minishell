# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykawakit <ykawakit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 09:24:28 by mevonuk           #+#    #+#              #
#    Updated: 2024/03/11 18:03:56 by ykawakit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall
LDFLAGS	+= -lreadline
LINKERS	= -L$(LIBFT_PATH) -lft -lreadline

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC = -I ./includes -I ./libft/ -I $(HOME)/readline/include

# Sources
SRC_PATH	=	src/
PARSER		=	$(addprefix parser/, parser.c putils.c make_strc.c \
				parse_redirect.c p_spliter.c get_data.c quotes.c putils2.c \
				parse_pipe.c variables.c lexer.c)
SIGNAL		=	$(addprefix signal/, signal.c)
EXEC		=	$(addprefix exec/, exec.c eutils.c pipe.c redirect.c background.c)
DEBUG		=	$(addprefix debug/, print.c)
BONUS		=	$(addprefix parser/, parse_andor.c parse_para.c)
BUILTIN		=	$(addprefix builtin/, manager.c cd.c echo.c env.c export.c unset.c pwd.c exit.c)
SRC			=	main.c clean.c check_tree.c \
				utils.c env.c env2.c error.c\
				$(PARSER) \
				$(SIGNAL) \
				$(EXEC) \
				$(DEBUG) \
				$(BONUS) \
				$(BUILTIN)

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LINKERS) -o $(NAME)
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
