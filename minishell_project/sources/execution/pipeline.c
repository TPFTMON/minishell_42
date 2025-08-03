/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:29:51 by sguan             #+#    #+#             */
/*   Updated: 2025/07/21 22:20:30 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_pipex(t_command *cmd)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->curr_index = 0;
	pipex->cmd_count = count_commands(cmd);
	pipex->input_fd = STDIN_FD;
	pipex->output_fd = STDOUT_FD;
	pipex->prev_pipe[0] = -1;
	pipex->prev_pipe[1] = -1;
	pipex->curr_pipe[0] = -1;
	pipex->curr_pipe[1] = -1;
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
	{
		free(pipex);
		return (NULL);
	}
	return (pipex);
}

void	child_cleanup_exit(t_shell_data *shell, t_command *cmd_head,
		t_pipex *pipex, int status)
{
	close_prev_pipes(pipex);
	free_pipex(pipex);
	close_heredoc_fds(cmd_head);
	free_cmd_list(&cmd_head);
	free_shell(shell);
	exit(status);
}

int	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	configure_execution_signals();
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (i == pipex->cmd_count - 1)
		{
			if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
		}
		i++;
	}
	configure_interactive_signals();
	return (last_status);
}

static int	pipeline_step(t_command *cmd_head, t_command *current,
				t_shell_data *shell, t_pipex *pipex)
{
	if (current->next_in_pipe)
	{
		if (pipe(pipex->curr_pipe) < 0)
			return (handle_fork_failure(pipex, pipex->curr_index));
	}
	else
	{
		pipex->curr_pipe[0] = -1;
		pipex->curr_pipe[1] = -1;
	}
	if (child_process(cmd_head, current, shell, pipex) != EXIT_SUCCESS)
		return (handle_fork_failure(pipex, pipex->curr_index));
	close_prev_pipes(pipex);
	pipex->prev_pipe[0] = pipex->curr_pipe[0];
	pipex->prev_pipe[1] = pipex->curr_pipe[1];
	return (EXIT_SUCCESS);
}

int	execute_pipeline(t_shell_data *shell, t_command *cmd)
{
	t_command	*current;
	t_pipex		*pipex;
	int			exit_status;

	pipex = init_pipex(cmd);
	if (!pipex)
		return (EXIT_FAILURE);
	current = cmd;
	while (current)
	{
		if (pipeline_step(cmd, current, shell, pipex) != EXIT_SUCCESS)
			return (handle_fork_failure(pipex, pipex->curr_index));
		current = current->next_in_pipe;
		pipex->curr_index++;
	}
	close_prev_pipes(pipex);
	exit_status = wait_for_children(pipex);
	free_pipex(pipex);
	return (exit_status);
}
