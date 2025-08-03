/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:11:55 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 16:47:56 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_redir_list(t_redirection *redirs)
// {
// 	t_redirection	*current;
// 	size_t			i;

// 	if (!redirs)
// 		return ;
// 	current = redirs;
// 	i = 0;
// 	while (current)
// 	{
// 		printf("|      (%zu) Type: ", i++);
// 		if (current->type == REDIR_INPUT)
// 			printf("[<]");
// 		else if (current->type == REDIR_OUTPUT)
// 			printf("[>]");
// 		else if (current->type == REDIR_APPEND)
// 			printf("[>>]");
// 		else if (current->type == REDIR_HEREDOC)
// 			printf("[<<]");
// 		else
// 			printf("UNKNOWN");
// 		printf(", Target: [%s], Heredoc FD: [%d]\n", current->target,
// 			current->heredoc_fd);
// 		current = current->next;
// 	}
// }

// void	print_cmd(t_command *cmd, size_t i)
// {
// 	printf("{=================================
// 		============================================}\n");
// 	if (!cmd)
// 	{
// 		printf("|Command(%zu): NULL\n", i);
// 		return ;
// 	}
// 	printf("|Command(%zu):\n", i);
// 	if (cmd->argv)
// 	{
// 		printf("|   Arguments:\n");
// 		for (int i = 0; cmd->argv[i]; i++)
// 			printf("|      (%d) [%s]\n", i, cmd->argv[i]);
// 	}
// 	else
// 		printf("|   NO arguments.\n");
// 	printf("|   Command Path: %s\n", cmd->cmd_path);
// 	if (cmd->redirections)
// 	{
// 		printf("|   Redirections:\n");
// 		print_redir_list(cmd->redirections);
// 	}
// 	else
// 		printf("|   NO redirections:\n");
// 	printf("|   PID: %d\n", cmd->pid);
// 	printf("{=====================================
// 		========================================}\n");
// 	printf("\\/\n");
// }

// void	print_cmd_list(t_command **pipeline_head)
// {
// 	t_command	*current;
// 	size_t		i;

// 	if (!*pipeline_head)
// 	{
// 		printf("|Command List: NULL\n");
// 		return ;
// 	}
// 	current = *pipeline_head;
// 	i = 0;
// 	while (current)
// 	{
// 		print_cmd(current, i++);
// 		current = current->next_in_pipe;
// 	}
// 	printf("\n");
// }
