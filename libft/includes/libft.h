/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:59:00 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 16:32:20 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 5000
# endif

# ifndef GNL_OPEN_MAX
#  define GNL_OPEN_MAX 256
# endif

# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS PROTOTYPES >>>>>>>>>>>>>>>>>>>>>

// get_next_line functions:
// gnl:
char				*get_next_line(int fd);
size_t				ft_strlen_gnl(char *string);
char				*ft_strchr_gnl(char *string, int occurance);
char				*ft_strjoin_gnl(char *rest, char *buff);
char				*ft_free_rest_gnl(char **rest);

// conversion functions:
// conversion:
int					ft_atoi(const char *str);
char				*ft_itoa(int n);

// string functions.
// str:
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strcpy(char *dest, const char *src);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strnstr(const char *big, const char *little, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);

// character functions.
// char:
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

// memory functions.
// mem:
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);

// error handling functions.
// error:
/*
 * Prints an error message to STDERR.
 * If msg is NULL,
 * uses perror to print the system error associated with 'object'.
 * If object is NULL, prints only msg.
 * Otherwise, prints "object: msg".
 */
void				print_error(char *object, char *msg);
int					print_error_with_code(char *object, char *msg,
						int error_code);
int					ft_dprintf(int fd, const char *format, ...);

// file descriptor functions.
// fd:
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);

// linked list functions.
// list:
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_strtol(const char *str, long *out);

#endif
