/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:28 by sguan             #+#    #+#             */
/*   Updated: 2025/07/21 00:00:46 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next_in_pipe;
	}
	return (count);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->pids && pipex->pids != NULL)
	{
		free(pipex->pids);
		pipex->pids = NULL;
	}
	free(pipex);
}

void	close_prev_pipes(t_pipex *pipex)
{
	if (pipex->prev_pipe[0] != -1)
	{
		close(pipex->prev_pipe[0]);
		pipex->prev_pipe[0] = -1;
	}
	if (pipex->prev_pipe[1] != -1)
	{
		close(pipex->prev_pipe[1]);
		pipex->prev_pipe[1] = -1;
	}
}

void	close_curr_pipes(t_pipex *pipex)
{
	if (pipex->curr_pipe[0] != -1)
	{
		close(pipex->curr_pipe[0]);
		pipex->curr_pipe[0] = -1;
	}
	if (pipex->curr_pipe[1] != -1)
	{
		close(pipex->curr_pipe[1]);
		pipex->curr_pipe[1] = -1;
	}
}

int	handle_fork_failure(t_pipex *pipex, int created_pids)
{
	while (--created_pids >= 0)
		waitpid(pipex->pids[created_pids], NULL, 0);
	close_prev_pipes(pipex);
	if (pipex->curr_pipe[0] != -1)
	{
		close(pipex->curr_pipe[0]);
	}
	if (pipex->curr_pipe[1] != -1)
	{
		close(pipex->curr_pipe[1]);
	}
	free_pipex(pipex);
	return (EXIT_FAILURE);
}
