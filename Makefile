# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 17:11:47 by ngjokaj           #+#    #+#              #
#    Updated: 2023/03/11 09:05:54 by ngjokaj          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

SRCS = 	main.c\
		philo_utils_00.c\
		philo_utils_01.c\
		philo_input.c\
		philo_eating.c\
		libft.c

OBJ = $(SRCS:.c=.o)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(OBJ)

re : fclean all
