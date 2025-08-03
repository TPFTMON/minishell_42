/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:06:56 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/20 19:02:58 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

# include <signal.h>
# include <sys/types.h>
# include <termios.h>

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
}							t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;
	int						heredoc_fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**argv;
	char					*cmd_path;
	t_redirection			*redirections;
	struct s_command		*next_in_pipe;
	pid_t					pid;
}							t_command;

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
}							t_internal_code;

typedef struct s_shell_data
{
	char					**envp;
	int						last_exit_status;

	t_command				*current_command;

	int						interactive_mode;
	char					*prompt;
	struct termios			original_termios;

	int						is_executing;
	t_internal_code			internal_code;

}							t_shell_data;

// <<<<<<<<<<<<<<<<<<<<< PARSING STRUCTURES >>>>>>>>>>>>>>>>>>>>>

// lexer:

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_INPUT,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ERROR
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*content;
	struct s_token			*next;
}							t_token;

typedef struct s_str_buffer
{
	char					*str;
	size_t					len;
	size_t					capacity;
}							t_str_buffer;

// <<<<<<<<<<<<<<<<<<<<< EXECUTION STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef struct s_pipex
{
	int						input_fd;
	int						output_fd;

	int						cmd_count;
	int						prev_pipe[2];
	int						curr_pipe[2];
	int						curr_index;

	pid_t					*pids;

}							t_pipex;

#endif
