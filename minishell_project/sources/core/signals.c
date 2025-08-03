/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 04:22:00 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/20 12:55:01 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_received_signal_value = 0;

static void	handle_sigint_interactive(int signo)
{
	(void)signo;
	g_received_signal_value = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Configures signals for when the shell is at an interactive prompt.
 * - SIGINT (Ctrl+C): Catches it with our handler to allow for prompt refresh.
 * - SIGQUIT (Ctrl+\): Ignores it, so it does nothing at the prompt.
 */
int	configure_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_interactive;
	if (sigaction(SIGINT, &sa_int, NULL) == FAIL)
	{
		perror("sigaction SIGINT");
		return (FAIL);
	}
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == FAIL)
	{
		perror("sigaction SIGQUIT");
		return (FAIL);
	}
	return (SUCCESS);
}

static void	handle_sigint_heredoc(int signo)
{
	(void)signo;
	g_received_signal_value = SIGINT;
	close(STDIN_FILENO);
}

int	configure_heredoc_signals(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_heredoc;
	if (sigaction(SIGINT, &sa_int, NULL) == FAIL)
	{
		perror("sigaction SIGINT for heredoc");
		return (FAIL);
	}
	return (SUCCESS);
}

// /**
//  * @brief Handler for SIGINT (Ctrl+C). Only sets the global flag.
//  */
// static void	handle_sigint_interactive(int signo)
// {
// 	(void)signo;
// 	g_received_signal_value = SIGINT;
// }

// /**
//  * @brief Checks the global signal flag and performs actions if a signal
//  * was received while at the interactive prompt.
//  *
//  * @param shell The main shell data structure.
//  */
// void	process_pending_signal(t_shell_data *shell)
// {
// 	if (g_received_signal_value == 0)
// 		return ;
// 	// This logic should only apply if a
// signal was received while at the prompt.
// 	// The is_executing flag in the main loop ensures this.
// 	if (g_received_signal_value == SIGINT)
// 	{
// 		shell->last_exit_status = 128 + SIGINT; // 128 + SIGINT
// 		// This sequence correctly refreshes
// the prompt after readline was interrupted.
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	// No action needed for SIGQUIT at the prompt, as it's set to SIG_IGN.
// 	g_received_signal_value = 0; // Reset the flag
// }
