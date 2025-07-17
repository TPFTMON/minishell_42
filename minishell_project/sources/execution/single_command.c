/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:20:02 by sguan             #+#    #+#             */
/*   Updated: 2025/07/18 00:52:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*try_path_cmd(char **paths, char *cmd)
{
	char	*path_with_slash;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		if (path_with_slash)
		{
			full_path = ft_strjoin(path_with_slash, cmd);
			free(path_with_slash);
			if (full_path && access(full_path, X_OK) == 0)
			{
				free_arr(paths);
				return (full_path);
			}
			free(full_path);
		}
		i++;
	}
	free_arr(paths);
	return (NULL);
}
int	find_command_path(t_command *cmd, char **envp)
{
	char	**paths;
	int		i;

	if (!cmd->argv[0] || cmd->argv[0][0] == '\0' || !envp)
		return (1);
	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], X_OK) == -1)
			return (1);
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
		return (0);
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (1);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (1);
	cmd->cmd_path = try_path_cmd(paths, cmd->argv[0]);
	if (!cmd->cmd_path)
		return (1);
	return (0);
}

int	execute_single_external(t_shell_data *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;

	if (find_command_path(cmd, shell->envp) == 1)
		return (ft_dprintf(2, "minishell: %s: command not found\n",
				cmd->argv[0]), 127);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		reset_child_signals();
		if (cmd->redirections)
			handle_redirections(cmd->redirections);
		execve(cmd->cmd_path, cmd->argv, shell->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		configure_execution_signals(); // A
		waitpid(pid, &status, 0);
		configure_interactive_signals(); // A
		if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		else
			status = WEXITSTATUS(status);
	}
	return (status);
}
