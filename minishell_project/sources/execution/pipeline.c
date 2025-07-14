/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:29:51 by sguan             #+#    #+#             */
/*   Updated: 2025/06/27 18:53:58 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_pipex(t_command *cmd)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->cmd_count = count_commands(cmd);
	pipex->input_fd = STDIN_FD;
	pipex->output_fd = STDOUT_FD;
	pipex->pipes = malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
	if (!pipex->pipes)
	{
		free(pipex);
		return (NULL);
	}
	pipex->pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
	{
		free(pipex->pipes);
		free(pipex);
		return (NULL);
	}
	return (pipex);
}

void	child_cleanup_exit(t_shell_data *shell, t_command *cmd_head,
		t_pipex *pipex, int status)
{
	free_pipex(pipex);
	free_command_list(cmd_head);
	free(shell);
	exit(status);
}

int	child_process(t_command *cmd_head, t_command *cmd, t_shell_data *shell,
		t_pipex *pipex, int i)
{
	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
		return (perror("fork"), EXIT_FAILURE);
	else if (pipex->pids[i] == 0)
	{
		if (i > 0)
			dup2(pipex->pipes[(i - 1) * 2], STDIN_FILENO);
		if (i < pipex->cmd_count - 1)
			dup2(pipex->pipes[i * 2 + 1], STDOUT_FILENO);
		if (cmd->redirections)
			handle_redirections(cmd->redirections);
		close_all_pipes(pipex);
		if (is_builtin(cmd->argv[0]))
			child_cleanup_exit(shell, cmd_head, pipex, execute_builtin(shell,
					cmd->argv));
		if (find_command_path(cmd, shell->envp) == 1)
		{
			ft_dprintf(2, "minishell: %s: command not found\n", cmd->argv[0]);
			child_cleanup_exit(shell, cmd_head, pipex, 127);
		}
		execve(cmd->cmd_path, cmd->argv, shell->envp);
		perror("execve");
		child_cleanup_exit(shell, cmd_head, pipex, EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}

int	execute_pipeline(t_shell_data *shell, t_command *cmd)
{
	t_pipex		*pipex;
	t_command	*current;
	int			i;
	int			exit_status;

	pipex = init_pipex(cmd);
	if (!pipex)
		return (EXIT_FAILURE);
	if (setup_pipeline(pipex) != EXIT_SUCCESS)
		return (free_pipex(pipex), EXIT_FAILURE);
	current = cmd;
	i = 0;
	while (current)
	{
		if (child_process(cmd, current, shell, pipex, i) != EXIT_SUCCESS)
			return (handle_fork_failure(pipex, i));
		current = current->next_in_pipe;
		i++;
	}
	close_all_pipes(pipex);
	exit_status = wait_for_children(pipex);
	free_pipex(pipex);
	return (exit_status);
}
