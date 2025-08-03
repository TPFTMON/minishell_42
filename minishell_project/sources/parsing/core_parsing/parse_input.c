/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:37:41 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/18 16:23:16 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(char *input, t_shell_data *shell)
{
	t_token		*tokens;
	t_command	*commands;

	if (input[0] == '\0')
	{
		shell->last_exit_status = 0;
		return (NULL);
	}
	tokens = lex_input(input, shell);
	if (!tokens)
		return (NULL);
	commands = build_cmd_list(&tokens, shell);
	free_token_list(&tokens);
	if (process_heredocs(&commands, shell) != SUCCESS)
	{
		free_cmd_list(&commands);
		return (NULL);
	}
	if (!commands)
		return (NULL);
	return (commands);
}
