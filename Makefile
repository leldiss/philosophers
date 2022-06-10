# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 14:10:51 by leldiss           #+#    #+#              #
#    Updated: 2022/06/10 15:26:16 by leldiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO	= philo_m

PHILO_BONUS	= philo_b

PHILO_SRCS = ./philo/philo.c \
				./philo/philo_actions.c \
				./philo/philo_init.c \
				./philo/utils.c \

PHILO_BONUS_SRCS = ./philo_bonus/philo.c \
				./philo_bonus/philo_actions.c \
				./philo_bonus/philo_init.c \
				./philo_bonus/utils.c \

OBJ = $(PHILO_SRCS:.c=.o)
OBJ_BONUS = $(PHILO_BONUS_SRCS:.c=.o)

HEADER	= ./philo/philo.h

HEADER_BONUS	= ./philo_bonus/philo.h

CC = gcc

RM = rm -f

FLAGS = -pthread -Wall -Wextra -Werror

all: $(PHILO)

$(PHILO) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(PHILO_SRCS) -o $(PHILO)

bonus: $(PHILO_BONUS)

$(PHILO_BONUS) : $(OBJ_BONUS) $(HEADER_BONUS)
	$(CC) $(FLAGS) $(PHILO_BONUS_SRCS) -o $(PHILO_BONUS)

clean:
		$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
		$(RM) $(PHILO) $(PHILO_BONUS)

re: fclean all

.PHONY : all clean fclean bonus re