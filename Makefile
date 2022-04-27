# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 12:46:58 by fgrossi           #+#    #+#              #
#    Updated: 2022/04/27 13:19:44 by fgrossi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PTHEAD_FLAG = -pthread

FILES =	philo \
		philo_utils2 \
		philo_utils \
		controls \

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

$(NAME) :	$(OBJS)
			$(CC) $(CFLAGS) $(PTHEAD_FLAG) -o $(NAME) $(OBJS)

all		:	$(NAME)

clean	:	
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

