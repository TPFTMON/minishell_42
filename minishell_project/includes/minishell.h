/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:40:31 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/04 23:28:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "have_fun.h"
#ifndef MINISHELL_H
# define MINISHELL_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <bits/sigaction.h> // !
# include <asm-generic/signal-defs.h> // !
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <curses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <term.h>
# include <limits.h> // For PATH_MAX
# include <stdbool.h> // For bool type

# include "../../libft/includes/libft.h"
# include "ms_structs.h"

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

extern volatile sig_atomic_t	g_received_signal_value;

# define ERROR -1

# define SYNTAX_ERROR_CODE 2

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>

//  -------------------- core --------------------
// initialization.c:
t_shell_data	*init_shell_data(char const **envp);

// signals.c:
int		setup_signals(void);
void	process_pending_signal(t_shell_data *shell);

// cleanup.c:
void	*free_envp(char **envp_copy);
void	*free_shell(t_shell_data *shell);

// prompt.c:

// -------------------- execution --------------------
// ...

// -------------------- parsing --------------------
// parse_input.c:
t_command	*parse_input(const char *input, t_shell_data *shell);

// lexer.c:
t_token	*tokenize_input(const char *input, t_shell_data *shell);
int		lex_input(const char *input, t_token **tokens, t_shell_data *shell);

// cleanup_pars.c:
void	free_token_list(t_token *tokens);
void	free_parsing(t_token *tokens, t_command *commands);

// expand_tokens.c:
t_token	*expand_tokens(t_token *tokens, t_shell_data *shell);

//       <TESTING>
void	test_exec(void);

#endif
