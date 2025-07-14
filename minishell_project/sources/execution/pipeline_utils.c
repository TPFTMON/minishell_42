/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:05:28 by sguan             #+#    #+#             */
/*   Updated: 2025/06/27 18:54:03 by sguan            ###   ########.fr       */
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

int	setup_pipeline(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(&pipex->pipes[i * 2]) < 0)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->pipes)
		free(pipex->pipes);
	free(pipex);
}

void	close_all_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 2 * (pipex->cmd_count - 1))
	{
		close(pipex->pipes[i]);
		i++;
	}
}
int	handle_fork_failure(t_pipex *pipex, int created_pids)
{
	while (--created_pids >= 0)
		waitpid(pipex->pids[created_pids], NULL, 0);
	close_all_pipes(pipex);
	free_pipex(pipex);
	return (EXIT_FAILURE);
}
