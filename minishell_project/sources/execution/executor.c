/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:42:53 by sguan             #+#    #+#             */
/*   Updated: 2025/07/19 17:06:50 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell_data *shell, char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, &(shell->envp)));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(shell->envp, args));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, &(shell->envp)));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, &(shell->envp)));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(shell, args));
	return (0);
}

int	exec_builtin_redir(t_shell_data *shell, char **args,
		t_redirection *redir)
{
	int	original_stdin;
	int	original_stdout;
	int	status;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	handle_cmd_redirections(redir);
	status = execute_builtin(shell, args);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
	return (status);
}

int	execute_single_command(t_shell_data *shell, t_command *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		if (cmd && cmd->redirections)
		{
			return (handle_redirections_only(cmd->redirections));
		}
		return (0);
	}
	if (is_builtin(cmd->argv[0]))
	{
		if (cmd->redirections)
			return (exec_builtin_redir(shell, cmd->argv, cmd->redirections));
		else
			return (execute_builtin(shell, cmd->argv));
	}
	return (execute_single_external(shell, cmd));
}

int	executor(t_shell_data *shell, t_command *cmd)
{
	int	status;

	if (!cmd->next_in_pipe)
	{
		status = execute_single_command(shell, cmd);
		shell->last_exit_status = status;
		return (status);
	}
	else
	{
		status = execute_pipeline(shell, cmd);
		shell->last_exit_status = status;
		return (status);
	}
}
