/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:06:56 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 23:47:40 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

# include <signal.h>
# include <sys/types.h>
# include <termios.h>



// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

// Enum for redirection types
typedef enum e_redir_type
{
	REDIR_INPUT,   // < infile
	REDIR_OUTPUT,  // > outfile (truncate)
	REDIR_APPEND,  // >> outfile (append)
	REDIR_HEREDOC, // << DELIMITER
	REDIR_NONE     // No redirection (used for error handling)
}						t_redir_type;

// Structure for a redirection
typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;               // Filename for <, >, >>; Delimiter for <<
	int						heredoc_fd;             // Read-end FD for heredoc content. Init to -1.
	struct s_redirection	*next; // Next redirection for the same command
}						t_redirection;

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
	// Process ID of this command after fork (set by executor). Init to 0 or -1.
	pid_t				pid;
}						t_command;

typedef enum e_internal_code
{
	OKAY,
	ERROR_CRITICAL,
	ERROR_SYNTAX_SINGLE_Q,
	ERROR_SYNTAX_DOUBLE_Q,
	ERROR_SYNTAX_UNEXPECTED_TOKEN,
	ERROR_SYNTAX_REDIR,
	ERROR_SYNTAX_PIPE,
	ERROR_UNIQUE
}						t_internal_code;

// The main shell structure holding overall state
typedef struct s_shell_data
{
	// A modifiable, NULL-terminated copy of the environment.
	char				**envp;
	// Exit status of the last executed foreground pipeline.
	int					last_exit_status;
	// Head of the parsed command list for the current input line.
	t_command			*current_command;
	// 1 if interactive, 0 otherwise (set at startup).
	int					interactive_mode;
	// The prompt string to display (e.g., "minishell> ").
	char				*prompt;
	// To restore terminal settings on exit.
	struct termios		original_termios;
	// For restoring stdin after redirections if needed. !!!
	// int						stdin_backup;
	// For restoring stdout. !!!
	// int						stdout_backup;
	// Flag: 1 if a command/pipeline is running, 0 if at prompt.
	int					is_executing;
	t_internal_code		internal_code;
}						t_shell_data;



// <<<<<<<<<<<<<<<<<<<<< PARSING STRUCTURES >>>>>>>>>>>>>>>>>>>>>

// lexer:

typedef enum e_token_type
{
	TOKEN_WORD,          // A command, argument, filename, or expanded string
	TOKEN_PIPE,          // |
	TOKEN_REDIR_INPUT,   // <
	TOKEN_REDIR_OUTPUT,  // > (truncate)
	TOKEN_REDIR_APPEND,  // >> (append)
	TOKEN_REDIR_HEREDOC, // << (heredoc)
	TOKEN_ERROR          // Represents lexical error
}						t_token_type;

typedef struct s_token
{
	t_token_type	type;      // The type of the token
	char			*content;  // The string content of the token
	struct s_token	*next;     // For creating a linked list of tokens
}						t_token;

typedef struct s_str_buffer
{
	char				*str;
	size_t				len;
	size_t				capacity;
}						t_str_buffer;

// <<<<<<<<<<<<<<<<<<<<< EXECUTION STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef struct s_pipex {
    // Input/output file descriptors for the entire pipeline
    int     input_fd;   // Input file descriptor (for < redirection at start)
    int     output_fd;  // Output file descriptor (for > redirection at end)

    // Pipeline information
    int     cmd_count;  // Number of commands in pipeline
    int     *pipes;     // Dynamically allocated array of pipe file descriptors
                       // Size would be 2 * (cmd_count - 1)

    // Process tracking
    pid_t   *pids;      // Dynamically allocated array of process IDs
                       // Size would be cmd_count
} t_pipex;


#endif
