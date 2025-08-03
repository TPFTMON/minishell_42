/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:49:50 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/21 20:32:32 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_received_signal_value;

int	process_pending_sig_heredoc(char *line, t_shell_data *shell)
{
	if (g_received_signal_value == SIGINT)
	{
		if (line)
			free(line);
		process_pending_signal(shell);
		return (FAIL);
	}
	return (SUCCESS);
}

int	readline_heredoc_loop(char *line, int *pipe_fds, t_redirection *redir,
		t_shell_data *shell)
{
	while (1)
	{
		line = readline("hd> ");
		if (process_pending_sig_heredoc(line, shell) == FAIL)
			return (FAIL);
		if (!line)
		{
			print_error("minishell", WARNING_MSG_HEREDOC_EOF);
			break ;
		}
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
	return (SUCCESS);
}

int	process_single_heredoc(t_redirection *redir, t_shell_data *shell)
{
	int		pipe_fds[2];
	char	*line;
	int		status;

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe (heredoc)");
		shell->last_exit_status = CRITICAL_ERROR;
		return (FAIL);
	}
	line = NULL;
	status = readline_heredoc_loop(line, pipe_fds, redir, shell);
	close(pipe_fds[1]);
	if (status == FAIL)
	{
		close(pipe_fds[0]);
		return (FAIL);
	}
	redir->heredoc_fd = pipe_fds[0];
	return (SUCCESS);
}

int	process_heredoc_loop(t_command **pipeline_head, t_shell_data *shell)
{
	t_command		*current_cmd;
	t_redirection	*current_redir;

	current_cmd = *pipeline_head;
	while (current_cmd != NULL)
	{
		current_redir = current_cmd->redirections;
		while (current_redir != NULL)
		{
			if (current_redir->type == REDIR_HEREDOC)
			{
				if (process_single_heredoc(current_redir, shell) != SUCCESS)
					return (FAIL);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next_in_pipe;
	}
	return (SUCCESS);
}

int	process_heredocs(t_command **pipeline_head, t_shell_data *shell)
{
	int				stdin_backup;
	int				status;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
	{
		perror("minishell: dup failed");
		return (FAIL);
	}
	configure_heredoc_signals();
	status = process_heredoc_loop(pipeline_head, shell);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	configure_interactive_signals();
	return (status);
}

// int	process_heredocs(t_command **pipeline_head, t_shell_data *shell)
// {
// 	t_command		*current_cmd;
// 	t_redirection	*current_redir;
// 	int				stdin_backup;

// 	stdin_backup = dup(STDIN_FILENO);
// 	if (stdin_backup == -1)
// 	{
// 		perror("minishell: dup failed");
// 		return (FAIL);
// 	}
// 	configure_heredoc_signals();
// 	current_cmd = *pipeline_head;
// 	while (current_cmd != NULL)
// 	{
// 		current_redir = current_cmd->redirections;
// 		while (current_redir != NULL)
// 		{
// 			if (current_redir->type == REDIR_HEREDOC)
// 			{
// 				if (process_single_heredoc(current_redir, shell) != SUCCESS)
// 				{
// 					dup2(stdin_backup, STDIN_FILENO);
// 					close(stdin_backup);
// 					configure_interactive_signals();
// 					return (FAIL);
// 				}
// 			}
// 			current_redir = current_redir->next;
// 		}
// 		current_cmd = current_cmd->next_in_pipe;
// 	}
// 	dup2(stdin_backup, STDIN_FILENO);
// 	close(stdin_backup);
// 	configure_interactive_signals();
// 	return (SUCCESS);
// }
