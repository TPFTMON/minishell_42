/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:15:00 by sguan             #+#    #+#             */
/*   Updated: 2025/07/21 22:20:11 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_external(t_command *cmd_head, t_command *cmd,
			t_shell_data *shell, t_pipex *pipex)
{
	char	*err_msg;
	char	*full_msg;

	if (find_command_path(cmd, shell->envp) == 1)
	{
		err_msg = ft_strjoin("minishell: ", cmd->argv[0]);
		full_msg = ft_strjoin(err_msg, ": command not found\n");
		free(err_msg);
		write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
		free(full_msg);
		child_cleanup_exit(shell, cmd_head, pipex, 127);
	}
	close_heredoc_fds(cmd_head);
	execve(cmd->cmd_path, cmd->argv, shell->envp);
	err_msg = ft_strjoin("minishell: ", cmd->argv[0]);
	full_msg = ft_strjoin(err_msg, ": ");
	free(err_msg);
	err_msg = ft_strjoin(full_msg, strerror(errno));
	free(full_msg);
	full_msg = ft_strjoin(err_msg, "\n");
	free(err_msg);
	write(STDERR_FILENO, full_msg, ft_strlen(full_msg));
	free(full_msg);
	child_cleanup_exit(shell, cmd_head, pipex, 126);
}

void	exec_cmd_in_child(t_command *cmd_head, t_command *cmd,
			t_shell_data *shell, t_pipex *pipex)
{
	int	status;

	status = 0;
	if (cmd->argv && cmd->argv[0])
	{
		if (is_builtin(cmd->argv[0]))
		{
			status = execute_builtin(shell, cmd->argv);
			child_cleanup_exit(shell, cmd_head, pipex, status);
		}
		else
			handle_child_external(cmd_head, cmd, shell, pipex);
	}
	else
		child_cleanup_exit(shell, cmd_head, pipex, status);
}

int	child_process(t_command *cmd_head, t_command *cmd, t_shell_data *shell,
				t_pipex *pipex)
{
	int	i;

	i = pipex->curr_index;
	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
		return (perror("fork"), EXIT_FAILURE);
	else if (pipex->pids[i] == 0)
	{
		reset_child_signals();
		if (pipex->prev_pipe[0] != -1)
			dup2(pipex->prev_pipe[0], STDIN_FILENO);
		if (pipex->curr_pipe[1] != -1)
			dup2(pipex->curr_pipe[1], STDOUT_FILENO);
		close_prev_pipes(pipex);
		close_curr_pipes(pipex);
		if (cmd->redirections)
			handle_cmd_redirections(cmd->redirections);
		exec_cmd_in_child(cmd_head, cmd, shell, pipex);
	}
	return (EXIT_SUCCESS);
}
