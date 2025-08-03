/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:01:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/21 22:02:11 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds(t_command *command_list)
{
	t_command		*current_cmd;
	t_redirection	*current_redir;

	current_cmd = command_list;
	while (current_cmd != NULL)
	{
		current_redir = current_cmd->redirections;
		while (current_redir != NULL)
		{
			if (current_redir->type == REDIR_HEREDOC
				&& current_redir->heredoc_fd != -1)
			{
				close(current_redir->heredoc_fd);
				current_redir->heredoc_fd = -1;
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next_in_pipe;
	}
}
