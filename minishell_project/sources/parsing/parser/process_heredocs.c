/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:49:50 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/18 00:53:02 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_received_signal_value;

int	process_single_heredoc(t_redirection *redir, t_shell_data *shell)
{
	int		pipe_fds[2];
	char	*line;

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe (heredoc)");
		shell->last_exit_status = CRITICAL_ERROR; // General error
		return (FAIL);
	}
	while (1)
	{
		line = readline("hd> "); // A simple prompt for heredoc
		// Check for SIGINT interruption immediately after readline returns
		if (g_received_signal_value == SIGINT)
		{
			if (line)
				free(line);
			close(pipe_fds[0]); // Cleanup the pipe
			close(pipe_fds[1]);
			shell->last_exit_status = 128 + SIGINT; // Set status for SIGINT
			return (FAIL);                          // Signal abortion
		}
		// Check for EOF (Ctrl+D)
		if (!line)
		{
			print_error(NULL, WARNING_MSG_HEREDOC_EOF);
			break ; // Exit loop, proceed with gathered input
		}
		// Check for delimiter
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ; // Delimiter found, exit loop
		}
		// Write the line to the pipe
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
	// CRITICAL: Close the write-end of the pipe. This sends an EOF to the read-end.
	close(pipe_fds[1]);
	// Store the read-end for the executor.
	redir->heredoc_fd = pipe_fds[0];
	return (SUCCESS);
}

int	process_heredocs(t_command **pipeline_head, t_shell_data *shell)
{
	t_command		*current_cmd;
	t_redirection	*current_redir;

	// if (configure_heredoc_signals() == FAIL)
	// 	return (print_error_with_code(NULL, ERROR_MSG_CRITICAL_SIGNALS_HD,
	// 			FAIL));
	current_cmd = *pipeline_head;
	while (current_cmd != NULL)
	{
		current_redir = current_cmd->redirections;
		while (current_redir != NULL)
		{
			if (current_redir->type == REDIR_HEREDOC)
			{
				// A heredoc was found, process it.
				if (process_single_heredoc(current_redir, shell) != SUCCESS)
				{
					// Processing was aborted (e.g., by Ctrl+C).
					// The main parser will now handle cleanup.
					return (FAIL);
				}
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next_in_pipe;
	}
	return (SUCCESS);
}
