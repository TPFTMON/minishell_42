/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:24:33 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/18 00:52:41 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pending_signal(t_shell_data *shell)
{
	if (g_received_signal_value == 0)
		return ;
	// This logic should only apply if a signal was received while at the prompt.
	// The is_executing flag in the main loop ensures this.
	if (g_received_signal_value == SIGINT)
		shell->last_exit_status = 128 + SIGINT;
	// No action needed for SIGQUIT at the prompt, as it's set to SIG_IGN.
	g_received_signal_value = 0; // Reset the flag
}
