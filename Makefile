# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 07:30:50 by abaryshe          #+#    #+#              #
#    Updated: 2025/06/24 14:53:08 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
MSLIB = mslib.a

INC_DIR = minishell_project/includes
OBJ_DIR = objects
LIBFT_DIR = libft
EXEC_DIR = minishell_project/sources/execution
PARS_DIR = minishell_project/sources/parsing
CORE_DIR = minishell_project/sources/core

FREM = rm -f
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}

#If you want to add any new files to EXEC part, just add them in the "execution" folder and then add the names of the files below
#         ||
#         \/      here, into this variable.
EXEC_FILES = test_exec.c
PARS_FILES = create_tokens.c cleanup_parsing.c str_buffer_funcs.c is_character.c test_create_tokens.c test_str_buffer.c
CORE_FILES = initialization.c cleanup.c signals.c

MAIN_SRC = minishell_project/sources/minishell.c
EXEC_SRCS = $(addprefix ${EXEC_DIR}/, ${EXEC_FILES})
PARS_SRCS = $(addprefix ${PARS_DIR}/, ${PARS_FILES})
CORE_SRCS = $(addprefix ${CORE_DIR}/, ${CORE_FILES})
SRCS = ${MAIN_SRC} ${EXEC_SRCS} ${PARS_SRCS} ${CORE_SRCS}
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

LIBFT = ${LIBFT_DIR}/libft.a

# Tell Make where to find .c files
vpath %.c minishell_project/sources ${EXEC_DIR} ${PARS_DIR} ${CORE_DIR}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

mslib: ${MSLIB}

${MSLIB}: ${OBJS} ${LIBFT}
	ar rcs ${MSLIB} ${OBJS} ${LIBFT}

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
	${FREM} ${MSLIB}
	${MAKE} -C ${LIBFT_DIR} fclean

re: fclean all

.PHONY: all clean fclean re
