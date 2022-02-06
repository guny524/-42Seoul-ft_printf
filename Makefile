# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:17:45 by min-jo            #+#    #+#              #
#    Updated: 2022/02/06 15:38:35 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libftprintf.a
HEADER		:=	ft_printf.h
SRC			:=	ft_printf.c print_str.c print_num.c
OBJ			:=	$(SRC:.c=.o)
BSRC		:=
BOBJ		:=	$(BSRC:.c=.o)

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
CPPFLAGS	:=	-I./

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	ar -rcs $@ $^

bonus:		$(OBJ) $(BOBJ)
	ar -rcs $(NAME) $?
	touch bonus

clean:
	rm -f $(OBJ) $(BOBJ) bonus

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re norm
