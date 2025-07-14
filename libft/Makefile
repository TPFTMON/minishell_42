# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 17:58:52 by abaryshe          #+#    #+#              #
#    Updated: 2025/07/08 21:38:13 by sguan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC_DIR = includes
OBJ_DIR = objects

CHAR_DIR = sources/char
CONV_DIR = sources/conversion
ERROR_DIR = sources/error
FD_DIR = sources/fd
GNL_DIR = sources/gnl
LIST_DIR = sources/list
MEM_DIR = sources/mem
STR_DIR = sources/str

CC = cc
CMPFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ${INC_DIR}
FREM = rm -f

# character functions in char directory:
CHAR_FILES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isprint.c ft_isspace.c ft_tolower.c ft_toupper.c
# conversion functions in conversion directory:
CONV_FILES = ft_atoi.c ft_itoa.c
# error handling functions in error directory:
ERROR_FILES = print_error.c print_error_with_code.c ft_dprintf.c
# file descriptor functions in fd directory:
FD_FILES = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
# get_next_line functions in gnl directory:
GNL_FILES = get_next_line.c get_next_line_utils.c
# linked list functions in list directory:
LIST_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c
# memory functions in mem directory:
MEM_FILES = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c
# string functions in str directory:
STR_FILES = ft_split.c  ft_strchr.c ft_strcpy.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_strcmp.c ft_strtol.c

CHAR_SRCS = $(addprefix ${CHAR_DIR}/, ${CHAR_FILES})
CONV_SRCS = $(addprefix ${CONV_DIR}/, ${CONV_FILES})
ERROR_SRCS = $(addprefix ${ERROR_DIR}/, ${ERROR_FILES})
FD_SRCS = $(addprefix ${FD_DIR}/, ${FD_FILES})
GNL_SRCS = $(addprefix ${GNL_DIR}/, ${GNL_FILES})
LIST_SRCS = $(addprefix ${LIST_DIR}/, ${LIST_FILES})
MEM_SRCS = $(addprefix ${MEM_DIR}/, ${MEM_FILES})
STR_SRCS = $(addprefix ${STR_DIR}/, ${STR_FILES})

SRCS = ${CHAR_SRCS} ${CONV_SRCS} ${ERROR_SRCS} ${FD_SRCS} ${GNL_SRCS} ${LIST_SRCS} ${MEM_SRCS} ${STR_SRCS}
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir $(SRCS:.c=.o)))

# Tell Make where to find .c files
vpath %.c ${CHAR_DIR} ${CONV_DIR} ${ERROR_DIR} ${FD_DIR} ${GNL_DIR} ${LIST_DIR} ${MEM_DIR} ${STR_DIR}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

# Compile .c files to .o files in the objects/ directory
${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}

fclean: clean
	${FREM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
