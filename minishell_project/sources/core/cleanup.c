/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:38:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 03:04:30 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_list(t_redirection **redirections)
{
	t_redirection	*current;
	t_redirection	*next;

	if (!*redirections || !redirections)
		return ;
	current = *redirections;
	while (current)
	{
		next = current->next;
		if (current->target)
			free(current->target);
		if (current)
			free(current);
		current = next;
	}
}

void	*free_string_array(char **str_array)
{
	int	i;

	if (!str_array)
		return (NULL);
	i = 0;
	while (str_array[i])
		i++;
	while (i >= 0)
	{
		free(str_array[i]);
		str_array[i] = NULL;
		i--;
	}
	free(str_array);
	return (NULL);
}

void	free_cmd(t_command *cmd)
{
	if(!cmd)
		return ;
	if (cmd->redirections)
		free_redir_list(&cmd->redirections);
	if (cmd->argv)
		free_string_array(cmd->argv);
	if (cmd)
		free(cmd);
}

void	free_cmd_list(t_command **pipeline_head)
{
	t_command	*current;
	t_command	*next;

	if (!*pipeline_head || !pipeline_head)
		return ;
	current = *pipeline_head;
	while (current)
	{
		next = current->next_in_pipe;
		free_cmd(current);
		current = next;
	}
}

void	*free_shell(t_shell_data *shell)
{
	if (!shell)
		return (NULL);
	if (shell->envp)
		free_string_array(shell->envp);
	if (shell->interactive_mode)
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->original_termios);
	free(shell);
	rl_clear_history();
	return (NULL);
}
