/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:40:31 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/24 18:04:19 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "have_fun.h"
#ifndef MINISHELL_H
# define MINISHELL_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include "../../libft/includes/libft.h"
# include "ms_structs.h"

# include <asm-generic/signal-defs.h> // !
# include <bits/sigaction.h>          // !
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h> // For PATH_MAX
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h> // For bool type
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

extern volatile sig_atomic_t	g_received_signal_value;

# define SUCCESS 0
# define FAIL -1

// EXIT error codes:
# define CRITICAL_ERROR 1
# define SYNTAX_ERROR 2
// ...
# define CMD_NOT_FOUND_ERROR 127

// internal error codes:
# define SYNTAX_ERROR_PIPE 3
# define SYNTAX_ERROR_REDIR 4
# define SYNTAX_ERROR_SINGLE_Q 5
# define SYNTAX_ERROR_DOUBLE_Q 6

# define ERROR_MSG_SINGLE_QUOTE "Syntax error: unclosed single quotes (\')\n"
# define ERROR_MSG_DOUBLE_QUOTE "Syntax error: unclosed double quotes (\")\n"

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>

//  -------------------- core --------------------
// initialization.c:
t_shell_data	*init_shell_data(char const **envp);

// signals.c:
int				setup_signals(void);
void			process_pending_signal(t_shell_data *shell);

// cleanup.c:
void			*free_envp(char **envp_copy);
void			*free_shell(t_shell_data *shell);

// prompt.c:

// -------------------- execution --------------------
// ...

// -------------------- parsing --------------------
// parse_input.c:
t_command		*parse_input(const char *input,
					t_shell_data *shell);

// lex_input.c:
t_token			*lex_input(const char *input,
					t_shell_data *shell);

// create_tokens.c:
t_token			*create_token(t_token_type type, char *content);
void			add_token_back(t_token **tokens,
					t_token *new_token);
void			create_redir_pipe_token(t_token **token,
					char *input, int *i);

// create_word_token.c:
void			create_word_token(t_token **token, char *input,
					int *i, t_shell_data *shell);

// str_buffer_funcs.c:
t_str_buffer	*init_str_buffer(size_t initial_capacity);
int				append_char_buffer(t_str_buffer *buf, char c);
int				append_str_buffer(t_str_buffer *buf,
					const char *str_to_append);
char			*finalize_buffer(t_str_buffer *buf);

// is_character.c:
int				is_metacharacter(int ch, int expanded);

// cleanup_pars.c:
void			free_token_list(t_token *tokens);
void			free_parsing(t_token *tokens,
					t_command *commands);
void			free_str_buffer(t_str_buffer *buf);

//      <<<TESTING>>>
// test_create_tokens.c:
void			print_token(t_token *token);
void			print_token_list(t_token *tokens);

// test_str_buffer.c:
void			print_str_buffer(t_str_buffer *buf);

#endif
