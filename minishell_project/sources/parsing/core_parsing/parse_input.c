/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:37:41 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/14 17:16:52 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(char *input, t_shell_data *shell)
{
	t_token		*tokens;
	t_command	*commands;

	tokens = lex_input(input, shell);
	if (!tokens)
		return (NULL);
	commands = build_cmd_list(&tokens, shell);
	free_token_list(&tokens);
	process_heredocs(&commands, shell);
	if (!commands)
		return (NULL);
	return (commands);
}

// t_command	*parse_input(char *input, t_shell_data *shell)
// {
// 	t_command	*command;

// 	if (!input || input[0] == '\0')
// 		return (NULL);
// 	command = malloc(sizeof(t_command)); // !!!
// 	if (!command)
// 		return (NULL);
// 	command->argv = NULL; // Initialize argv to NULL
// 	command->cmd_path = NULL; // Initialize cmd_path to NULL
// 	command->redirections = NULL; // Initialize redirections to NULL
// 	// Here you would typically parse the input string into command->argv,
// 	// command->cmd_path, and command->redirections.
// 	// For now, we just return the empty command structure.
// 	return (command);
// }
