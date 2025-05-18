/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:40:31 by abaryshe          #+#    #+#             */
/*   Updated: 2025/05/18 20:56:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "have_fun.h"
#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
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

// --- Project Specific Definitions ---

// Enum for redirection types
typedef enum e_redir_type
{
	REDIR_INPUT,  // < infile
	REDIR_OUTPUT, // > outfile (truncate)
	REDIR_APPEND, // >> outfile (append)
	REDIR_HEREDOC // << DELIMITER
}					t_redir_type;

// Structure for a single redirection
typedef struct s_redirection
{
	t_redir_type	type;
	char *target;               // Filename for <, >, >>; Delimiter for <<
	int heredoc_fd;             // Read-end FD for heredoc content. Init to -1.
	struct s_redirection *next; // Next redirection for the same command
}					t_redirection;

// Structure for a single command in a pipeline
typedef struct s_command
{
	char **argv;                    // Argument vector (e.g., {"ls", "-l", NULL}). Must be NULL-terminated.
	char *cmd_path;
		// Optional: Full path to executable (resolved by parser, NULL if not found/builtin).
	t_redirection *redirections;
		// Linked list of redirections for this command.
	struct s_command *next_in_pipe;
		// Pointer to the next command if connected by a pipe, NULL otherwise.
	pid_t pid;
		// Process ID of this command after fork (set by executor). Init to 0 or -1.
	int is_builtin;
		// Optional: Flag (0 or 1) if command is a builtin (set by parser).
}					t_command;

// The main shell structure holding overall state
typedef struct s_shell
{
	char **envp_copy;                             // A modifiable, NULL-terminated copy of the environment.
	int last_exit_status;
		// Exit status of the last executed foreground pipeline.
	t_command *current_command;
		// Head of the parsed command list for the current input line.
	volatile sig_atomic_t global_signal_received;
		// Stores the number of the signal received (e.g., SIGINT).
	int interactive_mode;                         // 1 if interactive, 0 otherwise (set at startup).
	struct termios original_termios;
		// To restore terminal settings on exit.
}					t_shell;

// --- Function Prototypes ---

// Example parser function prototype
t_command			*parse_line(const char *line, t_shell *shell_data);

// Example memory freeing function prototype
void				free_pipeline(t_command *pipeline);

// Example signal setup
void				setup_signal_handlers(void);

// Some testing:
void				test_exec(void);
void				test_pars(void);

#endif
