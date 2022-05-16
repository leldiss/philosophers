# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 14:29:55 by leldiss           #+#    #+#              #
#    Updated: 2022/05/16 00:07:38 by leldiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO	= philo

PHILO_SRCS = philo.c \
				./philo_actions.c \
				./philo_init.c \
				./utils.c \

OBJ = $(PHILO_SRCS:.c=.o)

HEADER	= philo.h

CC = gcc

RM = rm -f

FLAGS = -pthread

all: $(PHILO)

$(PHILO) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(PHILO_SRCS) -o $(PHILO)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(PHILO)

re: fclean all

.PHONY : all clean fclean re