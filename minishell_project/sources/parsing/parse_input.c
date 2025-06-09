/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:37:41 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 09:52:17 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(const char *input, t_shell_data *shell)
{
	t_token		*tokens;
	t_command	*commands;

	// 1. Tokenize
	tokens = tokenize_input(input, shell);
	if (!tokens)
	{ // Lexical error (e.g., unclosed quote)
		// shell->last_exit_status should be set by tokenize
		return (NULL);
	}
	// 2. Expand
	// expand_tokens might modify tokens in place or return a new list
	// For simplicity, assume it modifies in place for now.
	expand_tokens(tokens, shell);
	// If expansion itself can fail critically (e.g. malloc), check return.
	// 3. Build Command Structures
	commands = build_commands(tokens, shell);
	free_token_list(tokens);
		// Tokens are now represented in command structures or were invalid
	if (!commands)
	{ // Syntax error during command building
		// shell->last_exit_status should be set by build_commands
		return (NULL);
	}
	// 4. Process Heredocs
	if (process_heredocs(commands, shell) != TRUE)
	{ // Assuming process_heredocs returns status
		free_command_pipeline(commands);
		// shell->last_exit_status might be set if heredoc was interrupted by SIGINT
		return (NULL);
	}
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
