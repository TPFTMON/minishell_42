/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:24:33 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/18 16:46:21 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Configures signals for when the shell is waiting for child processes.
 * The parent shell should ignore the signals so they only affect the child.
 * - SIGINT (Ctrl+C): Ignored by the parent.
 * - SIGQUIT (Ctrl+\): Ignored by the parent.
 */
int	configure_execution_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == FAIL)
	{
		perror("sigaction SIGINT for execution");
		return (FAIL);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == FAIL)
	{
		perror("sigaction SIGQUIT for execution");
		return (FAIL);
	}
	return (SUCCESS);
}

/**
 * @brief Resets signals to their default OS behavior in a child process.
 * This is called after fork() but before execve().
 * - SIGINT (Ctrl+C): Default action (terminate).
 * - SIGQUIT (Ctrl+\): Default action (terminate and core dump).
 */
int	reset_child_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, NULL) == FAIL)
	{
		perror("sigaction SIGINT in child");
		return (FAIL);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == FAIL)
	{
		perror("sigaction SIGQUIT in child");
		return (FAIL);
	}
	return (SUCCESS);
}

void	process_pending_signal(t_shell_data *shell)
{
	if (g_received_signal_value == 0)
		return ;
	if (g_received_signal_value == SIGINT)
		shell->last_exit_status = 128 + SIGINT;
	g_received_signal_value = 0;
}

void	process_last_status(t_shell_data *shell)
{
	if (shell->last_exit_status == 128 + SIGINT)
		print_error(NULL, "\n");
	if (shell->last_exit_status == 128 + SIGQUIT)
		print_error(NULL, "Quit (core dumped)\n");
}
