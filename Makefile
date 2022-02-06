# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:17:45 by min-jo            #+#    #+#              #
#    Updated: 2022/02/06 15:42:22 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libftprintf.a
HEADER		:=	ft_printf.h
SRC			:=	ft_printf.c\
				state.c\
				conversion_num.c\
				print_char.c print_num.c
OBJ			:=	$(SRC:.c=.o)
BSRC		:=
BOBJ		:=	$(BSRC:.c=.o)

CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
CPPFLAGS	:=	-I./

all:		$(NAME)

%.o:		%.c $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -g -c $< -o $@

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

.PHONY:		all clean fclean re

# # if libftprintf.a exist in directory, result is not 0
# ISAREXIST	:=	ls | grep $(NAME) | wc -l | tr -d " "
# # if *bonus.o include in $(NAME) archive, result is not 0
# ISBONUSIN	:=	ar -t $(NAME) *bonus.o | wc -l | tr -d " "

# $(NAME):	$(COBJ)
# ifeq ($(ISAREXIST), 0)
# 	make COBJ="$(OBJ)" $(NAME)
# else
# ifneq ($(ISBONUSIN), 0)
# 	ar -d $(NAME) $(BOBJ)
# 	make COBJ="$(OBJ)" $(NAME)
# endif
# endif

# bonus:		$(BOBJ)
# ifeq ($(ISAREXIST), 0)
# 	make COBJ="$(BOBJ)" $(NAME)
# else
# ifeq ($(ISBONUSIN), 0)
# 	ar -d $(NAME) $(OBJ)
# 	make COBJ="$(BOBJ)" $(NAME)
# endif
# endif
