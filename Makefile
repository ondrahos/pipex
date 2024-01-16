#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 15:23:23 by ohosnedl          #+#    #+#              #
#    Updated: 2023/11/06 13:22:19 by ohosnedl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex
CFLAGS	:= -Wextra -Wall -Werror -g
LIBS	:= -lm -L./libft -lft
SRCS	:= $(wildcard *.c)
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

bonus: all

re: clean all

.PHONY: all, clean, fclean, re, bonus
