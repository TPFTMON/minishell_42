/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:38:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 09:55:50 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_envp(char **envp_copy)
{
	int	i;

	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp_copy[i])
		i++;
	while (i >= 0)
	{
		free(envp_copy[i]);
		envp_copy[i] = NULL;
		i--;
	}
	free(envp_copy);
	return (NULL);
}

// void	free_command_list(t_command *command)
// {
// }

// void	free_redirection(t_redirection *redir)
// {
// }

void	*free_shell(t_shell_data *shell)
{
	if (!shell)
		return (NULL);
	if (shell->envp)
		free_envp(shell->envp);
	if (shell->interactive_mode)
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_termios);
	free(shell);
	rl_clear_history();
	return (NULL);
}
