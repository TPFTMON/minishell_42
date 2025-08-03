/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:54:20 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/11 03:42:53 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_cmd(t_shell_data *shell)
{
	t_command	*cmd;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
	{
		shell->internal_code = ERROR_CRITICAL;
		return (NULL);
	}
	cmd->argv = NULL;
	cmd->cmd_path = NULL;
	cmd->redirections = NULL;
	cmd->next_in_pipe = NULL;
	cmd->pid = -1;
	return (cmd);
}

void	add_cmd_back(t_command **pipeline_head, t_command *new_cmd)
{
	t_command	*current;

	if (!new_cmd)
		return ;
	if (!*pipeline_head)
	{
		*pipeline_head = new_cmd;
		return ;
	}
	current = *pipeline_head;
	while (current->next_in_pipe)
		current = current->next_in_pipe;
	current->next_in_pipe = new_cmd;
}
