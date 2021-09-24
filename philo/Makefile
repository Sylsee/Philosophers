# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/13 01:56:04 by spoliart          #+#    #+#              #
#    Updated: 2021/09/24 23:30:23 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END		=	\e[0m

_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m

S= srcs/
O= objs/
I= includes/

NAME= philo

SRCS= main.c \
	  threads.c \
	  ft_atoi.c \
	  error.c


OBJS= $(SRCS:%.c=$O%.o)

INC= -I$I

CC= gcc
CFLAGS= -Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OBJS)
	@printf "\033[2K\r$(_GREEN) All $@ files compiled into '$O'. $(_END)✅\n"
	$(CC) $(CFLAGS) $(INC) $^ -o $@
	@printf "$(_GREEN) Binary '$(NAME)' created. $(_END)✅\n"

$O:
	@mkdir -p $@

$(OBJS):	| $O

$O%.o:	$S%.c
	@printf "\033[2K\r$(_YELLOW)Compiling $< $(_END)⌛"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@$(RM) -rf $O
	@printf "$(_RED) '$O' has been deleted. $(_END)🗑️\n"

fclean:	clean
	@$(RM) -f $(NAME)
	@printf "$(_RED) '$(NAME)' has been deleted. $(_END)🗑️\n"

re: fclean all

push: fclean
	@git add .
	@git commit -m "Philosophers"
	@git push

.PHONY:	all $(NAME) clean fclean re push
