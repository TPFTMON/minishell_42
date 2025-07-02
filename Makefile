# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 07:30:50 by abaryshe          #+#    #+#              #
#    Updated: 2025/07/02 00:42:51 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

TESTING = testing
MSLIB = mslib.a

INC_DIR = minishell_project/includes
OBJ_DIR = objects
LIBFT_DIR = libft

# CORE FOLDERS:
CORE_DIR = minishell_project/sources/core

# EXECUTION FOLDERS:
EXEC_DIR = minishell_project/sources/execution

# PARSING FOLDERS:
PARS_CORE_DIR = minishell_project/sources/parsing/core_parsing
PARS_LEX_DIR = minishell_project/sources/parsing/lexer
PARS_PARSE_DIR = minishell_project/sources/parsing/parser
PARS_TEST_DIR = minishell_project/sources/parsing/testing_parsing/print_functions

FREM = rm -f
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}

# --- CORE ---
CORE_FILES = initialization.c cleanup.c signals.c

# --- EXECUTION ---
EXEC_FILES = test_exec.c

# --- PARSING ---
PARS_CORE_FILES = parse_input.c cleanup_parsing.c codes.c
PARS_LEX_FILES = lexer.c token_utils.c is_character.c get_next_token.c str_buffer.c append_quotes.c expand_env_var.c errors_lexer.c
PARS_PARSE_FILES = parser.c cmd_utils.c process_redir.c process_word.c errors_parser.c
PARS_TEST_FILES = print_token.c print_buffer.c print_cmd.c
ALEKS_TEST = minishell_project/sources/parsing/testing_parsing/testing.c

MAIN_SRC = minishell_project/sources/minishell.c
EXEC_SRCS = $(addprefix ${EXEC_DIR}/, ${EXEC_FILES})
PARS_SRCS = $(addprefix ${PARS_CORE_DIR}/, ${PARS_CORE_FILES}) \
			$(addprefix ${PARS_LEX_DIR}/, ${PARS_LEX_FILES}) \
			$(addprefix ${PARS_PARSE_DIR}/, ${PARS_PARSE_FILES}) \
			$(addprefix ${PARS_TEST_DIR}/, ${PARS_TEST_FILES})
CORE_SRCS = $(addprefix ${CORE_DIR}/, ${CORE_FILES})
SRCS = ${MAIN_SRC} ${EXEC_SRCS} ${PARS_SRCS} ${CORE_SRCS}
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

LIBFT = ${LIBFT_DIR}/libft.a

# Tell Make where to find .c files
vpath %.c minishell_project/sources ${CORE_DIR} ${EXEC_DIR} ${PARS_CORE_DIR} ${PARS_LEX_DIR} ${PARS_PARSE_DIR} ${PARS_TEST_DIR}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

testing: ${LIBFT} ${MSLIB}
	${CC} ${CMPFLAGS} ${INCLUDES} ${ALEKS_TEST} ${MSLIB} ${LIBFT} -lreadline -o ${TESTING}

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

fullclear: fclean
	${FREM} ${TESTING}
	${FREM} ${MSLIB}

re: fclean all

.PHONY: all testing mslib clean fclean re
