/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:00:26 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/11 03:04:18 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses one simple command segment from the token stream.
 * A segment ends at a pipe token or the end of the token list.
 *
 * @param current_token A pointer to the current token pointer. This function
 * will advance the original pointer past the tokens it consumes.
 * @param shell The main shell data structure.
 * @return A pointer to a newly allocated and populated t_command,
 * or NULL on error.
 */
t_command	*get_next_cmd(t_token **token_now, t_shell_data *shell)
{
	t_command	*cmd;

	if ((*token_now)->type == TOKEN_PIPE)
	{
		shell->internal_code = ERROR_SYNTAX_PIPE;
		return (NULL);
	}
	cmd = init_cmd(shell);
	if (!cmd)
		return (NULL);
	while ((*token_now) && ((*token_now)->type != TOKEN_PIPE)
		&& (shell->internal_code == OKAY))
	{
		if (is_redir_token((*token_now)->type))
			process_redir_token(cmd, token_now, shell);
		else if ((*token_now)->type == TOKEN_WORD)
			process_word_token(cmd, token_now, shell);
		if (shell->internal_code != OKAY)
		{
			free_cmd(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

/**
 * @brief Builds a linked list of commands from a token list.
 * This is the main entry point for the syntax analysis stage.
 *
 * @param tokens A pointer to the head of the token list. The list will be
 * consumed by this function.
 * @param shell The main shell data structure for error reporting.
 * @return A pointer to the head of the command pipeline,
 * or NULL on syntax error.
 */
t_command	*build_cmd_list(t_token **tokens, t_shell_data *shell)
{
	t_command	*pipeline_head;
	t_command	*current_cmd;
	t_token		*token_now;

	pipeline_head = NULL;
	current_cmd = NULL;
	token_now = *tokens;
	while ((token_now))
	{
		current_cmd = get_next_cmd(&token_now, shell);
		if ((token_now) && (token_now->type == TOKEN_PIPE) && (token_now->next))
			token_now = token_now->next;
		else if ((token_now) && (shell->internal_code == OKAY))
			shell->internal_code = ERROR_SYNTAX_PIPE;
		if (shell->internal_code != OKAY)
		{
			free_cmd(current_cmd);
			print_and_set_parser_errors(shell);
			free_cmd_list(&pipeline_head);
			return (NULL);
		}
		if (current_cmd)
			add_cmd_back(&pipeline_head, current_cmd);
	}
	return (pipeline_head);
}

// t_command	*create_commands(t_command **pipeline_head, t_token **tokens,
// 		int internal_code)
// {
// 	t_command	*current_command;
// 	t_token		*current_token;

// 	current_token = *tokens;
// 	while ((current_token))
// 	{
// 		current_command = get_next_cmd(&current_token);
// 		if (current_command)
// 			add_cmd_back(pipeline_head, current_command);
// 		if (internal_code != 0)
// 		{
// 			print_parser_errors(internal_code);
// 			free_command_list(pipeline_head);
// 			return (NULL);
// 		}
// 	}
// 	return (*pipeline_head);
// }

// t_command	*build_cmd_list(t_token **tokens, t_shell_data *shell)
// {
// 	t_command	*pipeline_head;
// 	int			internal_code;

// 	pipeline_head = NULL;
// 	internal_code = 0;
// 	create_commands(&pipeline_head, tokens, internal_code);
// 	if (internal_code > 1)
// 		shell->last_exit_status = 2;
// 	else
// 		shell->last_exit_status = internal_code;
// 	internal_code = 0;
// 	if (shell->last_exit_status != 0)
// 		return (NULL);
// 	return (pipeline_head);
// }

// t_command	*build_cmd_list(t_token **tokens, t_shell_data *shell)
// {
// 	t_command	*pipeline_head;

// 	pipeline_head = NULL;
// 	internal_code = 0;
// 	create_commands(&pipeline_head, tokens, shell);
// 	if (internal_code > 1)
// 		shell->last_exit_status = 2;
// 	else
// 		shell->last_exit_status = internal_code;
// 	internal_code = 0;
// 	if (shell->last_exit_status != 0)
// 		return (NULL);
// 	return (pipeline_head);
// }
