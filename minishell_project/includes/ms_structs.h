/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:06:56 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 09:32:18 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

# include <sys/types.h>
# include <termios.h>
# include <signal.h>

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

// Enum for redirection types
typedef enum e_redir_type
{
	REDIR_INPUT,  // < infile
	REDIR_OUTPUT, // > outfile (truncate)
	REDIR_APPEND, // >> outfile (append)
	REDIR_HEREDOC // << DELIMITER
}					t_redir_type;

// Structure for a redirection
typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;               // Filename for <, >, >>; Delimiter for <<
	int						heredoc_fd;            // Read-end FD for heredoc content. Init to -1.
	struct s_redirection	*next;                 // Next redirection for the same command
}					t_redirection;

// Structure for a single command in a pipeline
typedef struct s_command
{
	// Argument vector (e.g., {"ls", "-l", NULL}). Must be NULL-terminated.
	char				**argv;
	// Full path to the command executable, NULL if not found. !!!
	char				*cmd_path;
	// Linked list of redirections for this command, NULL if no redirections.
	t_redirection		*redirections;
		// Pointer to the next command if connected by a pipe, NULL otherwise.
	struct s_command	*next_in_pipe;
		// Process ID of this command after fork (set by executor). Init to 0 or -1. !!!
	pid_t				pid;
		// Optional: Flag (0 or 1) if command is a builtin. !!!
	int					is_builtin;
}					t_command;

// The main shell structure holding overall state
typedef struct s_shell_data
{
		// A modifiable, NULL-terminated copy of the environment.
	char					**envp;
		// Exit status of the last executed foreground pipeline.
	int						last_exit_status;
		// Head of the parsed command list for the current input line.
	t_command				*current_command;
		// 1 if interactive, 0 otherwise (set at startup).
	int						interactive_mode;
		// The prompt string to display (e.g., "minishell> ").
	char					*prompt;
		// To restore terminal settings on exit.
	struct termios			original_termios;
		// For restoring stdin after redirections if needed. !!!
	// int						stdin_backup;
		// For restoring stdout. !!!
	// int						stdout_backup;
		// Flag: 1 if a command/pipeline is running, 0 if at prompt.
	int						is_executing;
		// Useful for signal handling logic in main loop.
}					t_shell_data;

// <<<<<<<<<<<<<<<<<<<<< PARSING STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef enum e_token_type
{
	TOKEN_WORD,          // A command, argument, filename, or expanded string
	TOKEN_PIPE,          // |
	TOKEN_REDIR_IN,      // <
	TOKEN_REDIR_OUT,     // > (truncate)
	TOKEN_REDIR_APPEND,  // >> (append)
	TOKEN_REDIR_HEREDOC, // << (here-document)
}	t_token_type;

typedef struct s_token
{
	char			*value;     // The string content of the token
	t_token_type	type;       // The type of the token
	struct s_token	*next;      // For creating a linked list of tokens
	// Optional: Might add flags later if needed, e.g., to indicate if a
	// TOKEN_WORD was originally quoted, which can influence expansion details
	// for more advanced scenarios, but for mandatory, keeping it simple is fine.
	int				flags;
}   t_token;

#endif
