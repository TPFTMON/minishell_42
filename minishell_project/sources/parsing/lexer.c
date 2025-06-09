/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 04:44:08 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 09:51:32 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_input(const char *input, t_token **tokens, t_shell_data *shell)
{
}

t_token	*tokenize_input(const char *input, t_shell_data *shell)
{
	t_token	*tokens;
	int				status;

	if (!input || input[0] == '\0')
		return (NULL);
	tokens = NULL;
	status = lex_input(input, &tokens, shell);
	if (status != TRUE)
	{
		shell->last_exit_status = status;
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}

// t_token	*tokenize(const char *input, t_shell_data *shell)
// {
	// t_token	*tokens;
	// int		status;
//
	// if (!input || input[0] == '\0')
		// return (NULL);
	// tokens = NULL;
	// status = lex_input(input, &tokens, shell);
	// if (status != TRUE)
	// {
		// shell->last_exit_status = status;
		// free_token_list(tokens);
		// return (NULL);
	// }
	// return (tokens);
// }
