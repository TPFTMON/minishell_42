# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 07:30:50 by abaryshe          #+#    #+#              #
#    Updated: 2025/05/16 01:34:03 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC_DIR = minishell_project/includes
OBJ_DIR = objects
LIBFT_DIR = libft
EXEC_DIR = minishell_project/sources/execution
PARS_DIR = minishell_project/sources/parsing

FREM = rm -f
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}

#If you want to add any new files to EXEC part, just add them in the "execution" folder and then add the names of the files below
#         ||
#         \/      here, into this variable.
EXEC_FILES = test_exec.c
PARS_FILES = test_pars.c

MAIN_SRC = minishell_project/sources/minishell.c
EXEC_SRCS = $(addprefix ${EXEC_DIR}/, ${EXEC_FILES})
PARS_SRCS = $(addprefix ${PARS_DIR}/, ${PARS_FILES})
SRCS = ${MAIN_SRC} ${EXEC_SRCS} ${PARS_SRCS}
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

LIBFT = ${LIBFT_DIR}/libft.a

# Tell Make where to find .c files
vpath %.c minishell_project/sources minishell_project/sources/execution minishell_project/sources/parsing

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

# Compile .c files to .o files in the objects/ directory
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	$(MAKE) -C ${LIBFT_DIR}

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} clean

fclean: clean
	${FREM} ${NAME}
	${MAKE} -C ${LIBFT_DIR} fclean

re: fclean all

.PHONY: all clean fclean re
