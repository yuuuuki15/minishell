# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mevonuk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:09:32 by mevonuk           #+#    #+#              #
#    Updated: 2024/01/22 13:37:24 by mevonuk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libft.a
CC =	cc
AR =	ar rcs
RM =	rm -rf

CFLAGS =	-Wall -Werror -Wextra

SRC_PATH =			./
OBJ_PATH = 			./obj/
INC =				./

SRC_NAME =	\
		ft_atoi.c ft_bzero.c ft_isalnum.c \
		ft_isalpha.c ft_isascii.c ft_memcpy.c \
		ft_strlcpy.c ft_tolower.c ft_strmapi.c \
		ft_isdigit.c ft_memmove.c ft_strlen.c ft_toupper.c \
		ft_isprint.c ft_memset.c ft_strncmp.c \
		ft_memchr.c ft_strchr.c ft_strnstr.c \
		ft_memcmp.c ft_strlcat.c ft_strrchr.c \
		ft_calloc.c ft_strdup.c ft_split.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_itoa.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstiter.c ft_lstclear.c ft_lstmap.c ft_atol.c \
		ft_itoa_unsigned_base.c ft_printf.c ft_putchar.c ft_putstr.c \
		ft_get_next_line.c ft_atof.c ft_strcmp.c \

SRC =		$(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ_NAME =	$(SRC_NAME:.c=.o)
OBJ =		$(addprefix $(OBJ_PATH), $(OBJ_NAME))

all:		$(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_PATH)

fclean:		clean
	@$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
