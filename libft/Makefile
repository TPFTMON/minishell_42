# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 17:58:52 by abaryshe          #+#    #+#              #
#    Updated: 2025/04/18 07:09:38 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
HEADER = libft.h
SOURCES = ${shell find -name '*.c'}
OBJECTS = ${SOURCES:.c=.o}
FREM = rm -f

all: ${NAME}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

%.o: %.c
	${CC} ${CMPFLAGS} -I ${HEADER} -c $< -o $@

clean:
	${FREM} ${OBJECTS} ${BONUS_OBJS}

fclean: clean
	${FREM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
