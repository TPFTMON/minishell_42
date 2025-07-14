# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/23 07:30:50 by abaryshe          #+#    #+#              #
#    Updated: 2025/07/14 17:16:15 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables for names and directiories ---
NAME = minishell

TESTING = testing
MSLIB = mslib.a

INC_DIR = minishell_project/includes
OBJ_DIR = objects
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

# core folders:
CORE_DIR = minishell_project/sources/core

# execution folders:
EXEC_DIR = minishell_project/sources/execution
BUILTINS_DIR = minishell_project/sources/execution/builtins

# parsing folders:
PARS_CORE_DIR = minishell_project/sources/parsing/core_parsing
PARS_LEX_DIR = minishell_project/sources/parsing/lexer
PARS_PARSE_DIR = minishell_project/sources/parsing/parser
PARS_TEST_DIR = minishell_project/sources/parsing/testing_parsing/print_functions

# --- Tools ---
FREM = rm -f
CC = cc
AR = ar rcs
CMPFLAGS = -Wall -Wextra -Werror -g # Added -g for debugging symbols
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR}/includes
LINKFLAGS = -lreadline # Linker flags

# --- Source Files ---
MAIN_SRC = minishell_project/sources/minishell.c

# core files
CORE_FILES = initialization.c \
			cleanup.c \
			signals.c

# execution files
EXEC_FILES = executor.c\
			single_command.c \
			pipeline.c \
			pipeline_utils.c\
			redirections.c

BUILTINS_FILES = builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c \
			builtin_utils.c

# parsing files
PARS_CORE_FILES = parse_input.c \
			cleanup_parsing.c \
			codes.c

PARS_LEX_FILES = lexer.c \
			token_utils.c \
			is_character.c \
			get_next_token.c \
			str_buffer.c \
			append_quotes.c \
			expand_env_var.c \
			errors_lexer.c

PARS_PARSE_FILES = parser.c \
			cmd_utils.c \
			process_redir.c \
			process_word.c \
			process_heredocs.c \
			errors_parser.c

PARS_TEST_FILES = print_token.c \
			print_buffer.c \
			print_cmd.c

ALEKS_TEST = minishell_project/sources/parsing/testing_parsing/testing.c

# --- Object File Lists from Source File Lists ---
MAIN_OBJ = $(addprefix ${OBJ_DIR}/, $(notdir $(MAIN_SRC:.c=.o)))
CORE_OBJS = $(addprefix ${OBJ_DIR}/, $(CORE_FILES:.c=.o))
EXEC_OBJS = $(addprefix ${OBJ_DIR}/, $(EXEC_FILES:.c=.o))
BUILTINS_OBJS = $(addprefix ${OBJ_DIR}/, $(BUILTINS_FILES:.c=.o))
PARS_CORE_OBJS = $(addprefix ${OBJ_DIR}/, $(PARS_CORE_FILES:.c=.o))
PARS_LEX_OBJS = $(addprefix ${OBJ_DIR}/, $(PARS_LEX_FILES:.c=.o))
PARS_PARSE_OBJS = $(addprefix ${OBJ_DIR}/, $(PARS_PARSE_FILES:.c=.o))
PARS_TEST_OBJS = $(addprefix ${OBJ_DIR}/, $(PARS_TEST_FILES:.c=.o))

# --- Full Source and Object Lists ---
OBJS = ${MAIN_OBJ} ${CORE_OBJS} ${EXEC_OBJS} ${BUILTINS_OBJS} ${PARS_CORE_OBJS} ${PARS_LEX_OBJS} ${PARS_PARSE_OBJS} ${PARS_TEST_OBJS}

# --- Main Rules ---
all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} ${LINKFLAGS} -o ${NAME}

${LIBFT}:
	$(MAKE) -C ${LIBFT_DIR}

# Rule for main.c
${MAIN_OBJ}: ${OBJ_DIR}/%.o: minishell_project/sources/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for core files
${CORE_OBJS}: ${OBJ_DIR}/%.o: ${CORE_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for execution files
${EXEC_OBJS}: ${OBJ_DIR}/%.o: ${EXEC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for builtins files
${BUILTINS_OBJS}: ${OBJ_DIR}/%.o: ${BUILTINS_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for parsing core files
${PARS_CORE_OBJS}: ${OBJ_DIR}/%.o: ${PARS_CORE_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for lexer files
${PARS_LEX_OBJS}: ${OBJ_DIR}/%.o: ${PARS_LEX_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for parser files
${PARS_PARSE_OBJS}: ${OBJ_DIR}/%.o: ${PARS_PARSE_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# Rule for parsing test/print files
${PARS_TEST_OBJS}: ${OBJ_DIR}/%.o: ${PARS_TEST_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

# --- Library and Testing Rules ---
TEST_DIR =  minishell_project/sources/execution/tests
TEST_SRCS = test_builtins_redir.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_TARGETS = test_builtins_redir

test: $(TEST_TARGETS)

test_builtins_redir: $(TEST_DIR)/test_builtins_redir.c $(filter-out objects/minishell.o, $(OBJS))
	@mkdir -p $(TEST_DIR)
	$(CC) $(CMPFLAGS) $(INCLUDES) -o $@ $^ $(LIBFT) ${LINKFLAGS}

testing: ${OBJS} ${LIBFT}
	${CC} ${CMPFLAGS} ${INCLUDES} ${ALEKS_TEST} $(filter-out ${MAIN_OBJ}, ${OBJS}) ${LIBFT} ${LINKFLAGS} -o ${TESTING}

# Compile .c files to .o files in the objects/ directory
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} clean

fclean: clean
	${FREM} ${NAME}
	${FREM} ${MSLIB}
	${FREM} ${TESTING}
	${MAKE} -C ${LIBFT_DIR} fclean

re: fclean all

.PHONY: all test testing clean fclean re

# SOURCES

# CORE_SRCS = $(addprefix ${CORE_DIR}/, ${CORE_FILES})

# EXEC_SRCS = $(addprefix ${EXEC_DIR}/, ${EXEC_FILES}) \
# 			$(addprefix ${BUILTINS_DIR}/, ${BUILTINS_FILES})

# PARS_SRCS = $(addprefix ${PARS_CORE_DIR}/, ${PARS_CORE_FILES}) \
# 			$(addprefix ${PARS_LEX_DIR}/, ${PARS_LEX_FILES}) \
# 			$(addprefix ${PARS_PARSE_DIR}/, ${PARS_PARSE_FILES}) \
# 			$(addprefix ${PARS_TEST_DIR}/, ${PARS_TEST_FILES})

# SRCS = ${MAIN_SRC} ${CORE_SRCS} ${EXEC_SRCS} ${PARS_SRCS}
# OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

# # Tell Make where to find .c files
# vpath %.c minishell_project/sources ${BUILTINS_DIR} ${CORE_DIR} ${EXEC_DIR} ${PARS_CORE_DIR} ${PARS_LEX_DIR} ${PARS_PARSE_DIR} ${PARS_TEST_DIR}
